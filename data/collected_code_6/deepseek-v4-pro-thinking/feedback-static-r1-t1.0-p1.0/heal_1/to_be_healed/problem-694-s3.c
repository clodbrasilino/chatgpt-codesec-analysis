#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int *extract_unique_values(const int *dictionary_values, size_t size, size_t *unique_count) {
    if (dictionary_values == NULL || unique_count == NULL || size == 0) {
        if (unique_count != NULL) {
            *unique_count = 0;
        }
        return NULL;
    }

    int *unique = malloc(size * sizeof(*unique));
    if (unique == NULL) {
        *unique_count = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        int found = 0;
        for (size_t j = 0; j < count; ++j) {
            if (unique[j] == dictionary_values[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[count++] = dictionary_values[i];
        }
    }

    int *resized = realloc(unique, count * sizeof(*resized));
    if (resized == NULL) {
        free(unique);
        *unique_count = 0;
        return NULL;
    }

    *unique_count = count;
    return resized;
}

int main(void) {
    int dictionary_values[] = {10, 20, 10, 30, 20, 40};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(dictionary_values)/sizeof(dictionary_values[0])', assigned value is 6
     */
    size_t size = sizeof(dictionary_values) / sizeof(dictionary_values[0]);
    size_t unique_count = 0;

    int *unique = extract_unique_values(dictionary_values, size, &unique_count);
    /* Possible weaknesses found:
     *  Condition 'size>0' is always true
     *  Condition 'size>0' is always true [knownConditionTrueFalse]
     */
    if (unique == NULL && size > 0) {
        fprintf(stderr, "Error: unable to extract unique values\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < unique_count; ++i) {
        printf("%d\n", unique[i]);
    }

    free(unique);
    return EXIT_SUCCESS;
}