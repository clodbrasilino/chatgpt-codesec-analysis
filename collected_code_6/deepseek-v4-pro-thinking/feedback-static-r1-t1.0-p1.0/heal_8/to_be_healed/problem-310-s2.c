#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tuple {
    char **items;
    size_t size;
} tuple_t;

static char *trim_and_copy(const char *start, const char *end) {
    if (start >= end) {
        char *copy = malloc(1);
        if (copy != NULL) {
            *copy = '\0';
        }
        return copy;
    }
    while (start < end && isspace((unsigned char)*start)) {
        start++;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'end>start' is not redundant
     */
    while (end > start && isspace((unsigned char)*(end - 1))) {
        end--;
    }
    /* Possible weaknesses found:
     *  Assignment 'length=(unsigned long)(end-start)', assigned value is less than 1
     */
    size_t length = (size_t)(end - start);
    char *copy = malloc(length + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  Condition 'length>0' is always false [knownConditionTrueFalse]
     *  Condition 'length>0' is always false
     */
    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, start, length);
    }
    copy[length] = '\0';
    return copy;
}

void tuple_free(tuple_t *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

int string_to_tuple(const char *str, size_t len, tuple_t *tuple) {
    if (str == NULL || tuple == NULL) {
        return -1;
    }
    tuple->items = NULL;
    tuple->size = 0;
    if (len == 0) {
        return 0;
    }
    const char *str_end = str + len;
    const char *cursor = str;
    for (;;) {
        const char *comma = memchr(cursor, ',', (size_t)(str_end - cursor));
        const char *end = comma != NULL ? comma : str_end;
        char *token = trim_and_copy(cursor, end);
        if (token == NULL) {
            tuple_free(tuple);
            return -1;
        }
        char **new_items = realloc(tuple->items, (tuple->size + 1) * sizeof(char *));
        if (new_items == NULL) {
            free(token);
            tuple_free(tuple);
            return -1;
        }
        tuple->items = new_items;
        tuple->items[tuple->size] = token;
        tuple->size++;
        if (comma == NULL) {
            break;
        }
        cursor = comma + 1;
    }
    return 0;
}

int main(void) {
    tuple_t tuple;
    const char input[] = "  apple, banana ,, cherry ,  ";
    if (string_to_tuple(input, sizeof(input) - 1, &tuple) != 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return 1;
    }
    for (size_t i = 0; i < tuple.size; i++) {
        printf("[%zu] = '%s'\n", i, tuple.items[i]);
    }
    tuple_free(&tuple);
    return 0;
}