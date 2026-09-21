#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    long *items;
    size_t count;
} Tuple;

static Tuple *tuple_create(size_t capacity)
{
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items = malloc(capacity * sizeof(long));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    t->count = 0;
    return t;
}

static void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got null
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got null
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got null
  */

static Tuple *string_to_tuple(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    size_t capacity = 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ',') {
            capacity++;
        }
    }

    Tuple *t = tuple_create(capacity);
    if (t == NULL) {
        return NULL;
    }

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        tuple_destroy(t);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len + 1);

    char *saveptr = NULL;
    char *token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while (isspace((unsigned char)*token)) {
            token++;
        }
        if (*token == '\0') {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }

        errno = 0;
        char *endptr = NULL;
        long value = strtol(token, &endptr, 10);
        if (errno == ERANGE || endptr == token) {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }
        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }
        if (*endptr != '\0') {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }

        if (t->count >= capacity) {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }
        t->items[t->count] = value;
        t->count++;

        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);

    if (t->count == 0) {
        tuple_destroy(t);
        return NULL;
    }

    return t;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL) {
        printf("(invalid)\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->count; i++) {
        printf("%ld", t->items[i]);
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *input = "1, 5, 7, 10, 13";

    Tuple *t = string_to_tuple(input);
    if (t == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Input string: \"%s\"\n", input);
    printf("Tuple: ");
    tuple_print(t);

    tuple_destroy(t);

    return EXIT_SUCCESS;
}