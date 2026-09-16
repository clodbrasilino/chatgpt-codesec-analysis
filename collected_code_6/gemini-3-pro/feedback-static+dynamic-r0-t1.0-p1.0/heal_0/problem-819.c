#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ElementFrequency;

ElementFrequency* count_consecutive_duplicates(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    if (length == 0) {
        *out_length = 0;
        return NULL;
    }

    ElementFrequency* result = malloc(length * sizeof(ElementFrequency));
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    result[0].value = list[0];
    result[0].count = 1;

    for (size_t i = 1; i < length; i++) {
        if (list[i] == result[result_index].value) {
            result[result_index].count++;
        } else {
            result_index++;
            result[result_index].value = list[i];
            result[result_index].count = 1;
        }
    }

    *out_length = result_index + 1;
    
    ElementFrequency* tmp = realloc(result, *out_length * sizeof(ElementFrequency));
    if (tmp != NULL) {
        result = tmp;
    }

    return result;
}

int main(void) {
    int list[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5};
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t out_length = 0;

    ElementFrequency* frequencies = count_consecutive_duplicates(list, length, &out_length);

    if (frequencies != NULL) {
        for (size_t i = 0; i < out_length; i++) {
            printf("%d: %d\n", frequencies[i].value, frequencies[i].count);
        }
        free(frequencies);
    } else {
        if (length > 0) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}