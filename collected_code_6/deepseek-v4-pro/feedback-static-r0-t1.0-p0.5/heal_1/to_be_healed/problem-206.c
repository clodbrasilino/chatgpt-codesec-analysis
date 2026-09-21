#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    int size;
} Tuple;

char *concatenate(const char *a, const char *b) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_a = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len_b = strlen(b);
    char *result = (char *)malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, a, len_a);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + len_a, b, len_b);
    result[len_a + len_b] = '\0';
    return result;
}

Tuple *adjacent_concatenation(Tuple *input) {
    if (input == NULL || input->size < 2) {
        return NULL;
    }

    Tuple *output = (Tuple *)malloc(sizeof(Tuple));
    if (output == NULL) {
        return NULL;
    }

    output->size = input->size - 1;
    output->items = (char **)malloc(sizeof(char *) * output->size);
    if (output->items == NULL) {
        free(output);
        return NULL;
    }

    for (int i = 0; i < output->size; i++) {
        output->items[i] = concatenate(input->items[i], input->items[i + 1]);
        if (output->items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(output->items[j]);
            }
            free(output->items);
            free(output);
            return NULL;
        }
    }

    return output;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (int i = 0; i < tuple->size; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

int main(void) {
    const char *data[] = {"ab", "cd", "ef", "gh"};
    int data_size = sizeof(data) / sizeof(data[0]);

    Tuple input;
    input.size = data_size;
    input.items = (char **)malloc(sizeof(char *) * data_size);
    if (input.items == NULL) {
        return 1;
    }

    for (int i = 0; i < data_size; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        input.items[i] = (char *)malloc(strlen(data[i]) + 1);
        if (input.items[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(input.items[j]);
            }
            free(input.items);
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(input.items[i], data[i]);
    }

    Tuple *result = adjacent_concatenation(&input);
    if (result == NULL) {
        free_tuple(&input);
        return 1;
    }

    for (int i = 0; i < result->size; i++) {
        printf("%s\n", result->items[i]);
    }

    free_tuple(&input);
    free_tuple(result);

    return 0;
}