#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

int compare_tuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    int cmpFirst = strcmp(tupleA->first, tupleB->first);
    if (cmpFirst != 0) return cmpFirst;
    return strcmp(tupleA->second, tupleB->second);
}

void assign_frequencies(Tuple *tuples, int count, TupleFrequency **result, int *result_count) {
    qsort(tuples, count, sizeof(Tuple), compare_tuples);

    *result = (TupleFrequency *)malloc(count * sizeof(TupleFrequency));
    if (*result == NULL) {
        *result_count = 0;
        return;
    }

    *result_count = 0;
    for (int i = 0; i < count; ++i) {
        if (*result_count == 0 || 
            (strcmp((*result)[*result_count - 1].tuple.first, tuples[i].first) != 0 ||
             strcmp((*result)[*result_count - 1].tuple.second, tuples[i].second) != 0)) {
            (*result)[*result_count].tuple = tuples[i];
            (*result)[*result_count].frequency = 1;
            (*result_count)++;
        } else {
            (*result)[*result_count - 1].frequency++;
        }
    }
}

int main() {
    Tuple tuples[] = {{"a", "b"}, {"c", "d"}, {"a", "b"}, {"e", "f"}, {"c", "d"}};
    int count = sizeof(tuples) / sizeof(tuples[0]);

    TupleFrequency *result;
    int result_count;

    assign_frequencies(tuples, count, &result, &result_count);

    for (int i = 0; i < result_count; ++i) {
        printf("(%s, %s): %d\n", result[i].tuple.first, result[i].tuple.second, result[i].frequency);
    }

    free(result);
    return 0;
}