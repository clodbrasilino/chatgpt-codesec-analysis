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

static void init_record_list(RecordList *list) {
    list->records = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int add_record(RecordList *list, int id, int count) {
    if (list->size == list->capacity) {
        int new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;
        Record *new_records = (Record *)realloc(list->records, new_capacity * sizeof(Record));
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

static void free_record_list(RecordList *list) {
    free(list->records);
    list->records = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int compare_records(const void *a, const void *b) {
    const Record *ra = (const Record *)a;
    const Record *rb = (const Record *)b;
    if (ra->count != rb->count) {
        return ra->count - rb->count;
    }
    return ra->id - rb->id;
}

int check_similar_occurrences(int *tuples, int tuple_count, int *result_ids, int max_results) {
    if (tuples == NULL || tuple_count <= 0 || result_ids == NULL || max_results <= 0) {
        return 0;
    }

    RecordList list;
    init_record_list(&list);

    int *ids = (int *)malloc(tuple_count * sizeof(int));
    if (ids == NULL) {
        return 0;
    }

    for (int i = 0; i < tuple_count; i++) {
        ids[i] = tuples[i];
    }

    qsort(ids, tuple_count, sizeof(int), compare_ints);

    int current_id = ids[0];
    int current_count = 1;

    for (int i = 1; i < tuple_count; i++) {
        if (ids[i] == current_id) {
            current_count++;
        } else {
            if (!add_record(&list, current_id, current_count)) {
                free(ids);
                free_record_list(&list);
                return 0;
            }
            current_id = ids[i];
            current_count = 1;
        }
    }

    if (!add_record(&list, current_id, current_count)) {
        free(ids);
        free_record_list(&list);
        return 0;
    }

    free(ids);

    qsort(list.records, list.size, sizeof(Record), compare_records);

    int result_count = 0;
    int i = 0;

    while (i < list.size) {
        int j = i + 1;
        while (j < list.size && list.records[j].count == list.records[i].count) {
            j++;
        }

        if (j - i > 1) {
            for (int k = i; k < j && result_count < max_results; k++) {
                result_ids[result_count++] = list.records[k].id;
            }
        }

        i = j;
    }

    free_record_list(&list);
    return result_count;
}

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int main(void) {
    int tuples[] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6};
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int result_ids[100];
    int result_count = check_similar_occurrences(tuples, tuple_count, result_ids, 100);

    printf("Records with similar occurrence counts: ");
    for (int i = 0; i < result_count; i++) {
        printf("%d ", result_ids[i]);
    }
    printf("\n");

    return 0;
}