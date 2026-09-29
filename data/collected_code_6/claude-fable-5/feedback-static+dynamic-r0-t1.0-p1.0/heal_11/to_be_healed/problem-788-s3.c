#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME_LEN 4096

typedef struct {
    char *name;
    int *values;
    size_t count;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t count);
void free_tuple(Tuple *t);
void print_tuple(const Tuple *t);

Tuple *create_tuple(const char *str, const int *list, size_t count)
{
    Tuple *t;
    size_t len;
    size_t values_size;

    if (str == NULL || (list == NULL && count > 0)) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    values_size = count * sizeof(int);

    len = strnlen(str, MAX_NAME_LEN);
    if (len >= MAX_NAME_LEN) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->name = malloc(len + 1);
    if (t->name == NULL) {
        free(t);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->name, str, len);
    t->name[len] = '\0';

    if (count > 0) {
        t->values = malloc(values_size);
        if (t->values == NULL) {
            free(t->name);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->values, list, values_size);
    } else {
        t->values = NULL;
    }

    t->count = count;
    return t;
}

void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->name);
        free(t->values);
        free(t);
    }
}

void print_tuple(const Tuple *t)
{
    size_t i;

    if (t == NULL || t->name == NULL) {
        return;
    }

    if (t->count > 0 && t->values == NULL) {
        return;
    }

    printf("(\"%s\", [", t->name);
    for (i = 0; i < t->count; i++) {
        printf("%d", t->values[i]);
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf("])\n");
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40};
    Tuple *t;

    t = create_tuple("example", numbers, sizeof(numbers) / sizeof(numbers[0]));
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}