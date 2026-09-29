#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096

typedef struct {
    char *items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

Tuple *string_to_tuple(const char *input)
{
    Tuple *tuple = NULL;
    size_t length = 0;
    char *items = NULL;

    if (input == NULL) {
        return NULL;
    }

    length = strnlen(input, MAX_INPUT_LENGTH);
    if (length == 0 || length >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    items = malloc(length + 1);
    if (items == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(items, input, length);
    items[length] = '\0';

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(items);
        return NULL;
    }

    tuple->items = items;
    tuple->count = length;
    return tuple;
}

void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        free(tuple);
    }
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL || tuple->items == NULL) {
        return;
    }

    printf("[");
    for (i = 0; i < tuple->count; i++) {
        printf("'%c'", tuple->items[i]);
        if (i + 1 < tuple->count) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(void)
{
    const char *inputs[] = { "python3.0", "item1", "15.10" };
    size_t i;
    size_t n = sizeof(inputs) / sizeof(inputs[0]);

    for (i = 0; i < n; i++) {
        Tuple *tuple = string_to_tuple(inputs[i]);

        if (tuple == NULL) {
            fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n",
                    inputs[i]);
            return EXIT_FAILURE;
        }

        print_tuple(tuple);

        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}