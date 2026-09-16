#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    size_t length = 0;
    size_t i = 0;
    size_t j = 0;
    char *items = NULL;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);
    if (length == 0) {
        return NULL;
    }

    items = malloc(length + 1);
    if (items == NULL) {
        return NULL;
    }

    for (i = 0; i < length; i++) {
        if (!isspace((unsigned char)input[i])) {
            items[j++] = input[i];
        }
    }
    items[j] = '\0';

    if (j == 0) {
        free(items);
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(items);
        return NULL;
    }

    tuple->items = items;
    tuple->count = j;
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

    fputc('[', stdout);
    for (i = 0; i < tuple->count; i++) {
        printf("'%c'", tuple->items[i]);
        if (i + 1 < tuple->count) {
            fputs(", ", stdout);
        }
    }
    fputs("]\n", stdout);
    fflush(stdout);
}

static int process_string(const char *str)
{
    Tuple *tuple = string_to_tuple(str);

    if (tuple == NULL) {
        fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n",
                str != NULL ? str : "(null)");
        return -1;
    }

    print_tuple(tuple);
    free_tuple(tuple);
    return 0;
}

int main(int argc, char *argv[])
{
    char buffer[1024];
    size_t len = 0;
    int i;
    int processed = 0;

    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (argv[i] == NULL || strlen(argv[i]) == 0) {
                continue;
            }
            if (process_string(argv[i]) != 0) {
                return EXIT_FAILURE;
            }
            processed = 1;
        }
    }

    if (!processed) {
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            len = strlen(buffer);
            while (len > 0 &&
                   (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
                buffer[len - 1] = '\0';
                len--;
            }

            if (len == 0) {
                continue;
            }

            if (process_string(buffer) != 0) {
                return EXIT_FAILURE;
            }
            processed = 1;
        }
    }

    fflush(stdout);
    return EXIT_SUCCESS;
}