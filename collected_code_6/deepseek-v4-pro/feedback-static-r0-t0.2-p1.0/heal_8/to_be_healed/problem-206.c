#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    int size;
} Tuple;

char *concatenate_adjacent(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL || tuple->size <= 0) {
        return NULL;
    }

    size_t *lengths = (size_t *)malloc(tuple->size * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    int i;
    for (i = 0; i < tuple->size; i++) {
        if (tuple->items[i] != NULL) {
            size_t len = strnlen(tuple->items[i], SIZE_MAX);
            if (len == SIZE_MAX) {
                free(lengths);
                return NULL;
            }
            lengths[i] = len;
            if (total_length > SIZE_MAX - len) {
                free(lengths);
                return NULL;
            }
            total_length += len;
        } else {
            lengths[i] = 0;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t current_pos = 0;
    for (i = 0; i < tuple->size; i++) {
        if (tuple->items[i] != NULL && lengths[i] > 0) {
            if (current_pos + lengths[i] > total_length) {
                free(lengths);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_pos, tuple->items[i], lengths[i]);
            current_pos += lengths[i];
        }
    }
    result[current_pos] = '\0';

    free(lengths);
    return result;
}

int main(void) {
    char *items1[] = {"Hello", " ", "World", "!"};
    Tuple tuple1 = {items1, 4};

    char *items2[] = {"C", "Programming", "Language"};
    Tuple tuple2 = {items2, 3};

    char *items3[] = {"No", NULL, "Concatenation"};
    Tuple tuple3 = {items3, 3};

    char *result1 = concatenate_adjacent(&tuple1);
    char *result2 = concatenate_adjacent(&tuple2);
    char *result3 = concatenate_adjacent(&tuple3);

    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    return 0;
}