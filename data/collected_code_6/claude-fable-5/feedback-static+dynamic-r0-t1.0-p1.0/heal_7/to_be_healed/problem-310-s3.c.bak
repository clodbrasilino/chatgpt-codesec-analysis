#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

Tuple *string_to_tuple(const char *str)
{
    Tuple *tuple;
    size_t length;

    if ((str == NULL) || (str[0] == '\0')) {
        return NULL;
    }

    length = strlen(str);

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = (char *)malloc(length + 1U);
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    memcpy(tuple->items, str, length);
    tuple->items[length] = '\0';
    tuple->count = length;

    return tuple;
}

void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        tuple->items = NULL;
        tuple->count = 0U;
        free(tuple);
    }
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if ((tuple == NULL) || (tuple->items == NULL) || (tuple->count == 0U)) {
        return;
    }

    (void)fputc('[', stdout);
    for (i = 0U; i < tuple->count; i++) {
        (void)printf("'%c'", tuple->items[i]);
        if (i < (tuple->count - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf("]\n");
    (void)fflush(stdout);
}

int main(void)
{
    const char *inputs[] = { "python3.0", "item1", "15.10" };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    size_t i;

    (void)setvbuf(stdout, NULL, _IONBF, 0);

    for (i = 0U; i < num_inputs; i++) {
        Tuple *tuple = string_to_tuple(inputs[i]);

        if (tuple == NULL) {
            (void)fprintf(stderr, "Failed to convert string to tuple\n");
            return EXIT_FAILURE;
        }

        print_tuple(tuple);
        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}