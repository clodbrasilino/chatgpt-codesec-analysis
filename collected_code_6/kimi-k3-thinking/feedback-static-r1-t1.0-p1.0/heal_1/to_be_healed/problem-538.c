#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

Tuple *string_list_to_tuple(char *list[], size_t count);
void free_tuple(Tuple *tuple);
void print_tuple(const Tuple *tuple);

int main(void)
{
    char *list[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = string_list_to_tuple(list, count);

    if (tuple == NULL) {
        fprintf(stderr, "Error: failed to convert string list to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple: ");
    print_tuple(tuple);

    free_tuple(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as const array [constParameter]
 */
Tuple *string_list_to_tuple(char *list[], size_t count)
{
    Tuple *tuple = NULL;
    size_t i = 0;

    if (list == NULL || count == 0) {
        return NULL;
    }

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = count;
    tuple->items = (char **)calloc(count, sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            free_tuple(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(list[i]);
        tuple->items[i] = (char *)malloc(len + 1);
        if (tuple->items[i] == NULL) {
            free_tuple(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->items[i], list[i], len + 1);
    }

    return tuple;
}

void free_tuple(Tuple *tuple)
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

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        printf("()\n");
        return;
    }

    printf("(");
    for (i = 0; i < tuple->size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("\"%s\"", tuple->items[i]);
    }
    if (tuple->size == 1) {
        printf(",");
    }
    printf(")\n");
}