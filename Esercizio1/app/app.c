#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../inc/array_list.h"

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

void print_array(ArrayList *al) {
    time(&time_start);
    printf("Starting to copy sorted array into file...\n");
    FILE *file = fopen("data/records_ordered", "w");
    for (int i = 0; i < ARRAY_CAPACITY; i++) {
        record *rec = get_obj(al, i);
        fprintf(file, "%d,%s,%d,%f\n", rec->id, rec->field1, rec->field2,
                rec->field3);
    }
    time(&time_end);
    printf("Done! array copied in %d seconds\n", (int) difftime(time_end, time_start));
}

void lald_data_into_array(ArrayList *al, char *filename) {
    time(&time_start);
    printf("Starting to copy records into array...\n");
    FILE *file = fopen(filename, "r");
    CATCH_ERROR
    while (!feof(file)) {
        record *rec = (record *) malloc(sizeof(record));
        rec->field1 = (char *) malloc(20);
        fscanf(file, "%d,%20[^,],%d,%f\n", &rec->id, rec->field1, &rec->field2, &rec->field3);
        CATCH_ERROR
        add_element(al, rec);
    }
    time(&time_end);
    printf("Done! records copied in %d seconds\n", (int) difftime(time_end, time_start));
}

void sort_array(ArrayList *al, char *settings) {
    void *cmp;
    printf("Starting to sort the array...\n");
    time(&time_start);
    if (strcmp(settings, "1") == 0) {
        cmp = (compare_fun) compare_field1;
    } else if (strcmp(settings, "2") == 0) {
        cmp = (compare_fun) compare_field2;
    } else {
        cmp = (compare_fun) compare_field3;
    }

/* NOTA: Come detto in precedenza, qui ti faccio notare come possa chiamare il */
/* metodo senza dover sapere i dettagli implementativi di ArrayList, come */
/* era richiesto precedentemente (perche' dovevi passare esplicitamente il */
/* lower e l'upper bound della prima chiamata ricorsiva */
    merge_sort(al, cmp);
    time(&time_end);
    printf("Done! array sorted in %d seconds\n", (int) difftime(time_end, time_start));
}

char *menu() {
    char *settings = (char *) malloc(sizeof(char) * 10);
    do {
        printf("SELECT SORT ORDER: 1 -> [char*]field1, 2 -> [int]field2, 3 -> [float]field3: ");
        scanf("%s", settings);
    } while ((strcmp(settings, "1") != 0) && (strcmp(settings, "2") != 0) && (strcmp(settings, "3") != 0));
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
    char *settings = menu();
    ArrayList *al = new_array_list(ARRAY_CAPACITY);
    lald_data_into_array(al, path);
    sort_array(al, settings);
    print_array(al);
    free_array_list(al);
    free(settings);
    exit(0);
}
