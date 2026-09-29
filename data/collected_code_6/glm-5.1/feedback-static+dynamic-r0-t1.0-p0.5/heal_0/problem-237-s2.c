#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int count;
} Tuple;

typedef struct {
    Tuple *tuple;
    int frequency;
} TupleRecord;

typedef struct {
    int frequency;
    int count;
} FrequencyResult;

int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int tuples_equal(Tuple *a, Tuple *b) {
    if (a->count != b->count) {
        return 0;
    }
    for (int i = 0; i < a->count; i++) {
        if (a->elements[i] != b->elements[i]) {
            return 0;
        }
    }
    return 1;
}

FrequencyResult *check_similar_occurrences(Tuple *tuples, int num_tuples, int *result_count) {
    if (tuples == NULL || num_tuples <= 0 || result_count == NULL) {
        return NULL;
    }

    TupleRecord *records = (TupleRecord *)malloc(num_tuples * sizeof(TupleRecord));
    if (records == NULL) {
        return NULL;
    }

    int unique_count = 0;

    for (int i = 0; i < num_tuples; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (tuples_equal(&tuples[i], &records[j].tuple[0])) {
                records[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            records[unique_count].tuple = &tuples[i];
            records[unique_count].frequency = 1;
            unique_count++;
        }
    }

    FrequencyResult *results = (FrequencyResult *)malloc(unique_count * sizeof(FrequencyResult));
    if (results == NULL) {
        free(records);
        return NULL;
    }

    int res_count = 0;

    for (int i = 0; i < unique_count; i++) {
        int found = 0;
        for (int j = 0; j < res_count; j++) {
            if (records[i].frequency == results[j].frequency) {
                results[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            results[res_count].frequency = records[i].frequency;
            results[res_count].count = 1;
            res_count++;
        }
    }

    free(records);
    *result_count = res_count;
    return results;
}

int main() {
    int a1[] = {1, 2};
    int a2[] = {3, 4};
    int a3[] = {1, 2};
    int a4[] = {5, 6};
    int a5[] = {3, 4};
    int a6[] = {1, 2};

    Tuple tuples[] = {
        {a1, 2},
        {a2, 2},
        {a3, 2},
        {a4, 2},
        {a5, 2},
        {a6, 2}
    };

    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int result_count = 0;

    FrequencyResult *results = check_similar_occurrences(tuples, num_tuples, &result_count);

    if (results != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("Frequency: %d, Count of such records: %d\n", results[i].frequency, results[i].count);
        }
        free(results);
    }

    return 0;
}