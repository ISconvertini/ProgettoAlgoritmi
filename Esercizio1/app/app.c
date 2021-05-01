#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../inc/oalib.h"

#define ARRAY_CAPACITY 20000000

time_t time_start, time_end;

typedef struct _record {
    int id;
    char *field1;
    int field2;
    float field3;
} record;

int compare_field1(record *record1, record *record2) {
    return strcmp(record1->field1, record2->field1);
}

int compare_field2(record *record1, record *record2) {
    return record1->field2 - record2->field2;
}

int compare_field3(record *record1, record *record2) {
    float result = record1->field3 - record2->field3;
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    } else {
        return 0;
    }
}

void print_array(OrderedArray *orderedArray) {
    time(&time_start);
    printf("Starting to copy sorted array into file...\n");
    FILE *file = fopen("data/records_ordered", "w");
    for (int i = 0; i < ARRAY_CAPACITY; i++) {
        record *rec = get_obj(orderedArray, i);
        fprintf(file, "%d,%s,%d,%f\n", rec->id, rec->field1, rec->field2,
                rec->field3);
    }
    time(&time_end);
    printf("Done! array copied in %d seconds\n", (int) difftime(time_end, time_start));
}

void load_data_into_array(OrderedArray *orderedArray, char *filename) {
    time(&time_start);
    printf("Starting to copy records into array...\n");
    FILE *file = fopen(filename, "r");
    CATCH_ERROR
    while (!feof(file)) {
        record *rec = (record *) malloc(sizeof(record));
        rec->field1 = (char *) malloc(20);
        fscanf(file, "%d,%20[^,],%d,%f\n", &rec->id, rec->field1, &rec->field2, &rec->field3);
        CATCH_ERROR
        insert_obj(orderedArray, rec);
    }
    time(&time_end);
    printf("Done! records copied in %d seconds\n", (int) difftime(time_end, time_start));
}

void sort_array(OrderedArray *oa, char **settings) {
    void *cmp;
    printf("Starting to sort the array...\n");
    time(&time_start);
    if (strcmp(settings[1], "1") == 0) {
        cmp = (compare_fun) compare_field1;
    } else if (strcmp(settings[1], "2") == 0) {
        cmp = (compare_fun) compare_field2;
    } else {
        cmp = (compare_fun) compare_field3;
    }
    if (strcmp(settings[0], "1") == 0) {
        quickSort(oa, cmp, sizeof(record));
    } else {
        insertionSort(oa, cmp, sizeof(record));
    }
    time(&time_end);
    printf("Done! array sorted in %d seconds\n", (int) difftime(time_end, time_start));
}

char **menu() {
    char **settings = (char **) malloc(sizeof(char *) * 2);
    do {
        printf("SELECT ALGORITHM: 1 -> QuickSort, 2 -> InsertionSort: ");
        settings[0] = (char *) malloc(sizeof(char) * 10);
        scanf("%s", settings[0]);
    } while ((strcmp(settings[0], "1") != 0) && (strcmp(settings[0], "2") != 0));
    CATCH_ERROR
    do {
        printf("SELECT SORT ORDER: 1 -> [char*]field1, 2 -> [int]field2, 3 -> [float]field3: ");
        settings[1] = (char *) malloc(sizeof(char) * 10);
        scanf("%s", settings[1]);
    } while ((strcmp(settings[1], "1") != 0) && (strcmp(settings[1], "2") != 0) && (strcmp(settings[1], "3") != 0));
    CATCH_ERROR
    return settings;
}

int main(int argc, char *argv[]) {
    char *path;
    if (strlen(argv[1]) != 0) {
        path = argv[1];
    } else {
        path = "data/records.csv";
    }
    char **settings = menu();
    OrderedArray *oa = new_ordered_array(ARRAY_CAPACITY);
    load_data_into_array(oa, path);
    sort_array(oa, settings);
    print_array(oa);
    free_ordered_array(oa);
    free(settings);
    exit(0);
}
