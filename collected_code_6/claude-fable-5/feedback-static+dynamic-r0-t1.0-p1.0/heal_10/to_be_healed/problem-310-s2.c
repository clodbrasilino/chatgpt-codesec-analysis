#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

typedef struct {
    char *items;
    size_t count;
    size_t capacity;
} Tuple;

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static Tuple *tuple_create(size_t capacity)
{
    if (capacity == 0 || capacity > MAX_INPUT_LEN) {
        return NULL;
    }

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
    t->capacity = capacity;
    return t;
}

static void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
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

    size_t len = bounded_strlen(str, MAX_INPUT_LEN);
    if (len == 0) {
        return NULL;
    }

    Tuple *t = tuple_create(len);
    if (t == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len && t->count < t->capacity; i++) {
        t->items[t->count] = str[i];
        t->count++;
    }

    return t;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL || t->items == NULL || t->count == 0) {
        printf("[]\n");
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

static void strip_newline(char *str)
{
    if (str == NULL) {
        return;
    }
    size_t len = bounded_strlen(str, MAX_INPUT_LEN);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

static int process_string(const char *str)
{
    Tuple *t = string_to_tuple(str);
    if (t == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return -1;
    }

    tuple_print(t);
    tuple_destroy(t);
    return 0;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    int status = EXIT_SUCCESS;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i] == NULL) {
                continue;
            }
            if (bounded_strlen(argv[i], MAX_INPUT_LEN) >= MAX_INPUT_LEN) {
                fprintf(stderr, "Input argument too long\n");
                status = EXIT_FAILURE;
                continue;
            }
            if (argv[i][0] == '\0') {
                continue;
            }
            if (process_string(argv[i]) != 0) {
                status = EXIT_FAILURE;
            }
        }
        return status;
    }

    memset(buffer, 0, sizeof(buffer));

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[sizeof(buffer) - 1] = '\0';
        strip_newline(buffer);

        if (buffer[0] == '\0') {
            continue;
        }

        if (process_string(buffer) != 0) {
            status = EXIT_FAILURE;
        }

        memset(buffer, 0, sizeof(buffer));
    }

    return status;
}