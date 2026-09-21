#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[64];
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

    size_t alloc_size = (size_t)list->size * sizeof(Record);
    if (alloc_size > SIZE_MAX / 2) {
        return result;
    }

    Record *sorted = (Record *)malloc(alloc_size);
    if (sorted == NULL) {
        return result;
    }

    size_t copy_size = (size_t)list->size * sizeof(Record);
    if (copy_size <= alloc_size) {
        memcpy(sorted, list->data, copy_size);
    } else {
        free(sorted);
        return result;
    }

    qsort(sorted, list->size, sizeof(Record), compare_records);

    size_t result_alloc_size = (size_t)k * sizeof(Record);
    if (result_alloc_size > SIZE_MAX / 2) {
        free(sorted);
        return result;
    }

    result.records = (Record *)malloc(result_alloc_size);
    if (result.records == NULL) {
        free(sorted);
        return result;
    }

    size_t result_copy_size = (size_t)k * sizeof(Record);
    if (result_copy_size <= result_alloc_size) {
        memcpy(result.records, sorted, result_copy_size);
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
            char safe_name[65];
            strncpy(safe_name, result.records[i].name, sizeof(safe_name) - 1);
            safe_name[sizeof(safe_name) - 1] = '\0';
            printf("ID: %d, Name: %s, Score: %.2f\n",
                   result.records[i].id,
                   safe_name,
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