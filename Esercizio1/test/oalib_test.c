
#include <stdlib.h>
#include "../inc/oalib.h"
#include "./Unity/unity.h"

typedef struct _record {
    int id;
    char *field;
} record;

static int compare_function(record *a, record *b) {
    return (a->id - b->id);
}

static record *init_record(int id, char *field) {
    record *new_record = (record *) malloc(sizeof(record));
    new_record->id = id;
    new_record->field = field;
    return new_record;
}

static void new_ordered_array_default_parameters() {
    OrderedArray *oa = new_ordered_array(100);
    TEST_ASSERT_EQUAL(0, get_size(oa));
    TEST_ASSERT_EQUAL(100, get_capacity(oa));
    free_ordered_array(oa);
}

static void insert_obj_in_array() {
    OrderedArray *oa = new_ordered_array(100);
    insert_obj(oa, init_record(1, "ciao"));
    insert_obj(oa, init_record(2, "prova"));
    insert_obj(oa, init_record(3, "fine"));
    record *record1 = get_obj(oa, 1);
    record *record2 = get_obj(oa, 2);

    TEST_ASSERT_EQUAL(3, get_size(oa));
    TEST_ASSERT_EQUAL(2, record1->id);
    TEST_ASSERT_EQUAL("fine", record2->field);
    free_ordered_array(oa);
}

static void remove_obj_from_array() {
    OrderedArray *oa = new_ordered_array(100);
    record *rec;
    insert_obj(oa, init_record(1, "ciao"));
    insert_obj(oa, init_record(2, "prova"));
    remove_obj(oa, 0);
    rec = get_obj(oa, 0);
    TEST_ASSERT_EQUAL(1, get_size(oa));
    TEST_ASSERT_EQUAL(2, rec->id);
    rec = get_obj(oa, 1);
    TEST_ASSERT_EQUAL(NULL, rec);
    free_ordered_array(oa);
}

static void test_quick_sort() {
    OrderedArray *oa = new_ordered_array(10);
    record* rec;
    insert_obj(oa, init_record(5, "a"));
    insert_obj(oa, init_record(2, "a"));
    quickSort(oa, (compare_fun) compare_function, sizeof(record));
    rec = get_obj(oa, 0);
    TEST_ASSERT_EQUAL(2, rec->id);
    rec = get_obj(oa, 1);
    TEST_ASSERT_EQUAL(5, rec->id);

    insert_obj(oa, init_record(4, "a"));
    insert_obj(oa, init_record(1, "a"));
    insert_obj(oa, init_record(3, "a"));
    quickSort(oa, (compare_fun) compare_function, sizeof(record));
    for (int i = 0; i < 5; i++) {
        rec = get_obj(oa, i);
        TEST_ASSERT_EQUAL(i + 1, rec->id);
    }
    free_ordered_array(oa);
}

static void test_insertion_sort() {
    OrderedArray *oa = new_ordered_array(10);
    record* rec;
    insert_obj(oa, init_record(5, "a"));
    insert_obj(oa, init_record(2, "a"));
    insertionSort(oa, (compare_fun) compare_function, sizeof(record));
    rec = get_obj(oa, 0);
    TEST_ASSERT_EQUAL(2, rec->id);
    rec = get_obj(oa, 1);
    TEST_ASSERT_EQUAL(5, rec->id);

    insert_obj(oa, init_record(4, "a"));
    insert_obj(oa, init_record(1, "a"));
    insert_obj(oa, init_record(3, "a"));
    insertionSort(oa, (compare_fun) compare_function, sizeof(record));
    for (int i = 0; i < 5; i++) {
        rec = get_obj(oa, i);
        TEST_ASSERT_EQUAL(i + 1, rec->id);
    }
    free_ordered_array(oa);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(new_ordered_array_default_parameters);
    RUN_TEST(insert_obj_in_array);
    RUN_TEST(remove_obj_from_array);
    RUN_TEST(test_quick_sort);
    RUN_TEST(test_insertion_sort);
    UNITY_END();
}
