#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float score;
} Record;

typedef struct {
    Record *data;
    int size;
} TupleList;

typedef struct {
    Record *records;
    int count;
} MinKResult;

int compare_records(const void *a, const void *b) {
    const Record *ra = (const Record *)a;
    const Record *rb = (const Record *)b;
    if (ra->score < rb->score) return -1;
    if (ra->score > rb->score) return 1;
    return ra->id - rb->id;
}

MinKResult find_min_k_records(const TupleList *list, int k) {
    MinKResult result;
    result.records = NULL;
    result.count = 0;

    if (list == NULL || list->data == NULL || list->size <= 0 || k <= 0) {
        return result;
    }

    if (k > list->size) {
        k = list->size;
    }

    size_t total_size = (size_t)list->size * sizeof(Record);
    if (total_size == 0 || total_size / sizeof(Record) != (size_t)list->size) {
        return result;
    }

    Record *sorted = (Record *)malloc(total_size);
    if (sorted == NULL) {
        return result;
    }

    if (total_size <= (size_t)list->size * sizeof(Record)) {
        memcpy(sorted, list->data, total_size);
    } else {
        free(sorted);
        return result;
    }

    qsort(sorted, list->size, sizeof(Record), compare_records);

    size_t result_size = (size_t)k * sizeof(Record);
    if (result_size == 0 || result_size / sizeof(Record) != (size_t)k) {
        free(sorted);
        return result;
    }

    result.records = (Record *)malloc(result_size);
    if (result.records == NULL) {
        free(sorted);
        return result;
    }

    if (result_size <= (size_t)k * sizeof(Record)) {
        memcpy(result.records, sorted, result_size);
    } else {
        free(sorted);
        free(result.records);
        result.records = NULL;
        return result;
    }

    result.count = k;

    free(sorted);
    return result;
}

void free_min_k_result(MinKResult *result) {
    if (result != NULL && result->records != NULL) {
        free(result->records);
        result->records = NULL;
        result->count = 0;
    }
}

int main(void) {
    Record data[] = {
        {1, "Alice", 85.5f},
        {2, "Bob", 72.0f},
        {3, "Charlie", 91.3f},
        {4, "David", 68.7f},
        {5, "Eve", 77.9f}
    };

    TupleList list;
    list.data = data;
    list.size = 5;

    int k = 3;
    MinKResult result = find_min_k_records(&list, k);

    if (result.records != NULL) {
        printf("Minimum %d records:\n", result.count);
        for (int i = 0; i < result.count; i++) {
            printf("ID: %d, Name: %s, Score: %.2f\n",
                   result.records[i].id,
                   result.records[i].name,
                   result.records[i].score);
        }
        free_min_k_result(&result);
    } else {
        printf("Failed to find minimum records.\n");
    }

    MinKResult empty_result = find_min_k_records(NULL, k);
    if (empty_result.records == NULL) {
        printf("Handled NULL list correctly.\n");
    }

    MinKResult zero_k_result = find_min_k_records(&list, 0);
    if (zero_k_result.records == NULL) {
        printf("Handled invalid k correctly.\n");
    }

    MinKResult large_k_result = find_min_k_records(&list, 10);
    if (large_k_result.records != NULL) {
        printf("Large k result count: %d\n", large_k_result.count);
        free_min_k_result(&large_k_result);
    }

    return 0;
}