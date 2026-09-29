#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int count;
} Record;

typedef struct {
    Record *records;
    size_t size;
    size_t capacity;
} RecordList;

static int compare_records(const void *a, const void *b) {
    const Record *ra = (const Record *)a;
    const Record *rb = (const Record *)b;
    return ra->count - rb->count;
}

static int init_record_list(RecordList *list, size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 16;
    }
    list->records = (Record *)malloc(initial_capacity * sizeof(Record));
    if (list->records == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return 0;
}

static void free_record_list(RecordList *list) {
    if (list->records != NULL) {
        free(list->records);
        list->records = NULL;
    }
    list->size = 0;
    list->capacity = 0;
}

static int add_record(RecordList *list, int id, int count) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Record *new_records = (Record *)realloc(list->records, new_capacity * sizeof(Record));
        if (new_records == NULL) {
            return -1;
        }
        list->records = new_records;
        list->capacity = new_capacity;
    }
    list->records[list->size].id = id;
    list->records[list->size].count = count;
    list->size++;
    return 0;
}

static int find_record_index(const RecordList *list, int id) {
    for (size_t i = 0; i < list->size; i++) {
        if (list->records[i].id == id) {
            return (int)i;
        }
    }
    return -1;
}

int check_similar_occurrences(const int *tuples, size_t tuple_count, int *result_ids, size_t *result_count) {
    if (tuples == NULL || result_ids == NULL || result_count == NULL) {
        return -1;
    }
    if (tuple_count == 0) {
        *result_count = 0;
        return 0;
    }

    RecordList list;
    if (init_record_list(&list, 16) != 0) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; i++) {
        int idx = find_record_index(&list, tuples[i]);
        if (idx >= 0) {
            list.records[idx].count++;
        } else {
            if (add_record(&list, tuples[i], 1) != 0) {
                free_record_list(&list);
                return -1;
            }
        }
    }

    if (list.size == 0) {
        free_record_list(&list);
        *result_count = 0;
        return 0;
    }

    qsort(list.records, list.size, sizeof(Record), compare_records);

    size_t max_similar_count = 0;
    size_t current_similar_count = 1;
    for (size_t i = 1; i < list.size; i++) {
        if (list.records[i].count == list.records[i - 1].count) {
            current_similar_count++;
        } else {
            if (current_similar_count > max_similar_count) {
                max_similar_count = current_similar_count;
            }
            current_similar_count = 1;
        }
    }
    if (current_similar_count > max_similar_count) {
        max_similar_count = current_similar_count;
    }

    if (max_similar_count <= 1) {
        free_record_list(&list);
        *result_count = 0;
        return 0;
    }

    size_t result_index = 0;
    current_similar_count = 1;
    for (size_t i = 1; i < list.size; i++) {
        if (list.records[i].count == list.records[i - 1].count) {
            current_similar_count++;
        } else {
            if (current_similar_count == max_similar_count) {
                for (size_t j = i - current_similar_count; j < i; j++) {
                    result_ids[result_index++] = list.records[j].id;
                }
            }
            current_similar_count = 1;
        }
    }
    if (current_similar_count == max_similar_count) {
        for (size_t j = list.size - current_similar_count; j < list.size; j++) {
            result_ids[result_index++] = list.records[j].id;
        }
    }

    *result_count = result_index;
    free_record_list(&list);
    return 0;
}

int main(void) {
    int tuples[] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int *result_ids = (int *)malloc(tuple_count * sizeof(int));
    size_t result_count = 0;

    if (result_ids == NULL) {
        return 1;
    }

    if (check_similar_occurrences(tuples, tuple_count, result_ids, &result_count) != 0) {
        free(result_ids);
        return 1;
    }

    printf("Records with similar occurrence counts: ");
    for (size_t i = 0; i < result_count; i++) {
        printf("%d ", result_ids[i]);
    }
    printf("\n");

    free(result_ids);
    return 0;
}