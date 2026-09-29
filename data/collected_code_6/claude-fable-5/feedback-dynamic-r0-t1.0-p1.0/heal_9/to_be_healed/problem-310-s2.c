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
    if (capacity == 0) {
        capacity = 1;
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
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
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
        printf("[]\n");
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
}

static int process_string(const char *str)
{
    Tuple *t = string_to_tuple(str);
    if (t == NULL) {
        fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n",
                str ? str : "(null)");
        return -1;
    }
    tuple_print(t);
    fflush(stdout);
    tuple_destroy(t);
    return 0;
}

int main(int argc, char *argv[])
{
    char buffer[1024];

    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i] == NULL || argv[i][0] == '\0') {
                continue;
            }
            if (process_string(argv[i]) != 0) {
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (buffer[0] == '\0') {
            continue;
        }

        if (process_string(buffer) != 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}