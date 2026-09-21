#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
} StringTuple;

StringTuple *string_list_to_tuple(const char *list[], size_t count)
{
    StringTuple *tuple;
    size_t i;
    size_t j;

    if (list == NULL || count == 0) {
        return NULL;
    }

    tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = malloc(count * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = 0;

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            for (j = 0; j < tuple->size; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        tuple->items[i] = malloc(strlen(list[i]) + 1);
        if (tuple->items[i] == NULL) {
            for (j = 0; j < tuple->size; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(tuple->items[i], list[i]);
        tuple->size++;
    }

    return tuple;
}

void free_string_tuple(StringTuple *tuple)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (i = 0; i < tuple->size; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }

    free(tuple);
}

void print_string_tuple(const StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        printf("()\n");
        return;
    }

    printf("(");
    for (i = 0; i < tuple->size; i++) {
        printf("\"%s\"", tuple->items[i]);
        if (i + 1 < tuple->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *list[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(list) / sizeof(list[0]);
    StringTuple *tuple = string_list_to_tuple(list, count);

    if (tuple == NULL) {
        fprintf(stderr, "Error: failed to convert string list to tuple\n");
        return EXIT_FAILURE;
    }

    print_string_tuple(tuple);

    free_string_tuple(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}