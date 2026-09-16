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

Tuple *string_to_tuple(const char *str)
{
    Tuple *tuple = NULL;
    size_t length;
    size_t i;

    if ((str == NULL) || (str[0] == '\0')) {
        return NULL;
    }

    length = strlen(str);

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = (char *)malloc(length * sizeof(char));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (i = 0U; i < length; i++) {
        tuple->items[i] = str[i];
    }
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

    (void)printf("(");
    for (i = 0U; i < tuple->count; i++) {
        (void)printf("'%c'", tuple->items[i]);
        if (i < (tuple->count - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf(")\n");
}

int main(void)
{
    const char *inputs[] = { "python3.0", "item1", "15.10" };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    size_t i;

    for (i = 0U; i < num_inputs; i++) {
        Tuple *tuple = string_to_tuple(inputs[i]);

        if (tuple == NULL) {
            (void)fprintf(stderr, "Failed to convert string to tuple\n");
            return EXIT_FAILURE;
        }

        (void)printf("Input string: \"%s\"\n", inputs[i]);
        (void)printf("Tuple: ");
        print_tuple(tuple);

        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}