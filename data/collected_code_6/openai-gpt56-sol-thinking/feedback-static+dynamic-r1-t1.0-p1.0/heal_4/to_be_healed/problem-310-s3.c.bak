#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    unsigned char *items;
    size_t length;
} CharTuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

CharTuple *string_to_tuple(const char *string)
{
    CharTuple *tuple;
    size_t length;

    if (string == NULL) {
        return NULL;
    }

    length = strlen(string);

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->length = length;

    if (length != 0) {
        tuple->items = malloc(length * sizeof(*tuple->items));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }

        memcpy(tuple->items, string, length);
    }

    return tuple;
}

void free_tuple(CharTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->items);
    free(tuple);
}

int print_tuple(const CharTuple *tuple)
{
    size_t i;

    if (tuple == NULL ||
        (tuple->length != 0 && tuple->items == NULL)) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->length; ++i) {
        unsigned char value = tuple->items[i];

        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }

        switch (value) {
            case '\'':
                if (fputs("\\'", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\\':
                if (fputs("\\\\", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\n':
                if (fputs("\\n", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\r':
                if (fputs("\\r", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\t':
                if (fputs("\\t", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\b':
                if (fputs("\\b", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\f':
                if (fputs("\\f", stdout) == EOF) {
                    return -1;
                }
                break;

            case '\v':
                if (fputs("\\v", stdout) == EOF) {
                    return -1;
                }
                break;

            default:
                if (value >= 32 && value <= 126) {
                    if (fputc((int)value, stdout) == EOF) {
                        return -1;
                    }
                } else if (fprintf(stdout, "\\x%02X",
                                   (unsigned int)value) < 0) {
                    return -1;
                }
                break;
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return fflush(stdout) == EOF ? -1 : 0;
}

int read_input_line(char **result)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity - 1) {
            char *expanded;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            expanded = realloc(buffer, new_capacity);

            if (expanded == NULL) {
                free(buffer);
                return -1;
            }

            buffer = expanded;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (length != 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *result = buffer;

    return 0;
}

int main(int argc, char **argv)
{
    const char *input;
    char *input_buffer = NULL;
    CharTuple *tuple;
    int status;

    if (argc == 2) {
        input = argv[1];
    } else if (argc == 1) {
        if (read_input_line(&input_buffer) != 0) {
            return EXIT_FAILURE;
        }

        input = input_buffer;
    } else {
        const char *program_name =
            argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    tuple = string_to_tuple(input);
    free(input_buffer);

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    status = print_tuple(tuple);
    free_tuple(tuple);

    return status == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}