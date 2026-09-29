#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    int *values;
    size_t count;
} ResultSet;

static int count_occurrences(const Tuple *tuples, size_t num_tuples, int value)
{
    int count = 0;
    size_t i;
    size_t j;

    for (i = 0; i < num_tuples; i++) {
        for (j = 0; j < tuples[i].size; j++) {
            if (tuples[i].elements[j] == value) {
                count++;
            }
        }
    }
    return count;
}

static int already_collected(const ResultSet *result, int value)
{
    size_t i;

    for (i = 0; i < result->count; i++) {
        if (result->values[i] == value) {
            return 1;
        }
    }
    return 0;
}

int extract_single_elements(const Tuple *tuples, size_t num_tuples, ResultSet *result)
{
    size_t total = 0;
    size_t i;
    size_t j;

    if (tuples == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < num_tuples; i++) {
        if (tuples[i].elements == NULL && tuples[i].size > 0) {
            return -1;
        }
        total += tuples[i].size;
    }

    result->values = NULL;
    result->count = 0;

    if (total == 0) {
        return 0;
    }

    result->values = malloc(total * sizeof(int));
    if (result->values == NULL) {
        return -1;
    }

    for (i = 0; i < num_tuples; i++) {
        for (j = 0; j < tuples[i].size; j++) {
            int value = tuples[i].elements[j];
            if (!already_collected(result, value) &&
                count_occurrences(tuples, num_tuples, value) == 1) {
                result->values[result->count] = value;
                result->count++;
            }
        }
    }

    return 0;
}

void free_result(ResultSet *result)
{
    if (result != NULL) {
        free(result->values);
        result->values = NULL;
        result->count = 0;
    }
}

int main(void)
{
    int t1[] = {3, 4, 5};
    int t2[] = {4, 5, 7};
    int t3[] = {1, 4};
    Tuple tuples[3];
    ResultSet result;
    size_t i;

    tuples[0].elements = t1;
    tuples[0].size = sizeof(t1) / sizeof(t1[0]);
    tuples[1].elements = t2;
    tuples[1].size = sizeof(t2) / sizeof(t2[0]);
    tuples[2].elements = t3;
    tuples[2].size = sizeof(t3) / sizeof(t3[0]);

    if (extract_single_elements(tuples, 3, &result) != 0) {
        fprintf(stderr, "Error extracting elements\n");
        return EXIT_FAILURE;
    }

    printf("Elements occurring singly: ");
    for (i = 0; i < result.count; i++) {
        printf("%d ", result.values[i]);
    }
    printf("\n");

    free_result(&result);
    return EXIT_SUCCESS;
}