#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int count;
} Record;

typedef struct {
    Record *records;
    int size;
    int capacity;
} RecordList;

void init_record_list(RecordList *list) {
    list->records = NULL;
    list->size = 0;
    list->capacity = 0;
}

void free_record_list(RecordList *list) {
    free(list->records);
    list->records = NULL;
    list->size = 0;
    list->capacity = 0;
}

int add_record(RecordList *list, int id, int count) {
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;
        Record *new_records = realloc(list->records, new_capacity * sizeof(Record));
        if (new_records == NULL) {
            return 0;
        }
        list->records = new_records;
        list->capacity = new_capacity;
    }
    list->records[list->size].id = id;
    list->records[list->size].count = count;
    list->size++;
    return 1;
}

int find_record(RecordList *list, int id) {
    for (int i = 0; i < list->size; i++) {
        if (list->records[i].id == id) {
            return i;
        }
    }
    return -1;
}

int check_similar_occurrences(const int *tuples, int tuple_count, int tuple_size) {
    if (tuples == NULL || tuple_count <= 0 || tuple_size <= 0) {
        return 0;
    }

    RecordList list;
    init_record_list(&list);

    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < tuple_size; j++) {
            int value = tuples[i * tuple_size + j];
            int index = find_record(&list, value);
            if (index == -1) {
                if (!add_record(&list, value, 1)) {
                    free_record_list(&list);
                    return 0;
                }
            } else {
                list.records[index].count++;
            }
        }
    }

    int first_count = -1;
    int result = 1;

    for (int i = 0; i < list.size; i++) {
        if (first_count == -1) {
            first_count = list.records[i].count;
        } else if (list.records[i].count != first_count) {
            result = 0;
            break;
        }
    }

    free_record_list(&list);
    return result;
}

int main(void) {
    int tuples1[] = {1, 2, 3, 2, 3, 4, 3, 4, 5};
    int tuple_count1 = 3;
    int tuple_size1 = 3;

    int tuples2[] = {1, 2, 2, 3, 3, 4};
    int tuple_count2 = 3;
    int tuple_size2 = 2;

    int tuples3[] = {1, 2, 3, 4, 5, 6};
    int tuple_count3 = 2;
    int tuple_size3 = 3;

    printf("Test 1: %d\n", check_similar_occurrences(tuples1, tuple_count1, tuple_size1));
    printf("Test 2: %d\n", check_similar_occurrences(tuples2, tuple_count2, tuple_size2));
    printf("Test 3: %d\n", check_similar_occurrences(tuples3, tuple_count3, tuple_size3));

    return 0;
}