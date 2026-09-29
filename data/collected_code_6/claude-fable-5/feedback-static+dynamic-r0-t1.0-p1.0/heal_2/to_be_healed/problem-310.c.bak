#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

typedef struct {
    char *items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

Tuple *string_to_tuple(const char *input)
{
    Tuple *tuple = NULL;
    size_t capacity = 4;
    size_t count = 0;
    size_t i;
    size_t len;
    char *items = NULL;
    char *resized = NULL;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);

    items = malloc(capacity * sizeof(char));
    if (items == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (isspace((unsigned char)input[i])) {
            continue;
        }

        if (count == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(items);
                return NULL;
            }
            capacity *= 2;
            resized = realloc(items, capacity * sizeof(char));
            if (resized == NULL) {
                free(items);
                return NULL;
            }
            items = resized;
        }

        items[count] = input[i];
        count++;
    }

    if (count == 0) {
        free(items);
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(items);
        return NULL;
    }

    tuple->items = items;
    tuple->count = count;
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

    printf("(");
    for (i = 0; i < tuple->count; i++) {
        printf("'%c'", tuple->items[i]);
        if (i + 1 < tuple->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *inputs[] = {
        "python 3.0",
        "item1",
        "15.10"
    };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    size_t i;

    for (i = 0; i < num_inputs; i++) {
        Tuple *tuple = string_to_tuple(inputs[i]);

        if (tuple == NULL) {
            fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n", inputs[i]);
            return EXIT_FAILURE;
        }

        printf("Input string: \"%s\"\n", inputs[i]);
        printf("Tuple: ");
        print_tuple(tuple);

        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}