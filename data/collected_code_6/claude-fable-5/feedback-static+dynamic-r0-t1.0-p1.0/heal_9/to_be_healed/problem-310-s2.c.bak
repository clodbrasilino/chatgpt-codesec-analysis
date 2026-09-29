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
    t->items = malloc(capacity > 0 ? capacity : 1);
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
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

static Tuple *string_to_tuple(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    Tuple *t = tuple_create(len);
    if (t == NULL) {
        return NULL;
    }

    if (len > 0) {
        memcpy(t->items, str, len);
    }
    t->count = len;

    return t;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL) {
        printf("(invalid)\n");
        fflush(stdout);
        return;
    }
    printf("[");
    for (size_t i = 0; i < t->count; i++) {
        printf("'%c'", t->items[i]);
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(void)
{
    char buffer[4096];

    setvbuf(stdout, NULL, _IONBF, 0);

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (buffer[0] == '\0') {
            continue;
        }

        Tuple *t = string_to_tuple(buffer);
        if (t == NULL) {
            fprintf(stderr, "Failed to convert string to tuple\n");
            continue;
        }

        tuple_print(t);

        tuple_destroy(t);
    }

    fflush(stdout);
    return EXIT_SUCCESS;
}