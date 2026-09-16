#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *items;
    size_t count;
} Tuple;

static Tuple *tuple_create(size_t capacity)
{
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items = malloc(capacity * sizeof(char));
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
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

static Tuple *string_to_tuple(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    Tuple *t = tuple_create(len);
    if (t == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        t->items[i] = str[i];
    }
    t->count = len;

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
        printf("'%c'", t->items[i]);
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *inputs[] = {
        "python3.0",
        "item1",
        "15.10"
    };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < num_inputs; i++) {
        Tuple *t = string_to_tuple(inputs[i]);
        if (t == NULL) {
            fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n", inputs[i]);
            return EXIT_FAILURE;
        }

        printf("Input string: \"%s\"\n", inputs[i]);
        printf("Tuple: ");
        tuple_print(t);

        tuple_destroy(t);
    }

    return EXIT_SUCCESS;
}