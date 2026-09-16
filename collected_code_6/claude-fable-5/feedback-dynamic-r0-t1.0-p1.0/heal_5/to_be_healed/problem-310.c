#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    size_t i = 0;
    char *items = NULL;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);
    if (length == 0) {
        return NULL;
    }

    items = malloc((length + 1) * sizeof(char));
    if (items == NULL) {
        return NULL;
    }

    for (i = 0; i < length; i++) {
        items[i] = input[i];
    }
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

    if (tuple == NULL) {
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
    char buffer[1024];
    Tuple *tuple = NULL;
    size_t len = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }

        if (len == 0) {
            continue;
        }

        tuple = string_to_tuple(buffer);
        if (tuple == NULL) {
            fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n", buffer);
            return EXIT_FAILURE;
        }

        print_tuple(tuple);

        free_tuple(tuple);
        tuple = NULL;
    }

    return EXIT_SUCCESS;
}