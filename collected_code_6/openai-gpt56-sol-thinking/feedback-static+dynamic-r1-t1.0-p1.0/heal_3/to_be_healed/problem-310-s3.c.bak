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

    tuple = malloc(sizeof *tuple);
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->length = length;

    if (length > 0) {
        tuple->items = malloc(length);
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
    if (tuple != NULL) {
        free(tuple->items);
        free(tuple);
    }
}

int print_tuple(const CharTuple *tuple)
{
    size_t index;

    if (tuple == NULL || (tuple->length > 0 && tuple->items == NULL)) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (index = 0; index < tuple->length; ++index) {
        unsigned char value = tuple->items[index];

        if (index > 0 && fputs(", ", stdout) == EOF) {
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
            default:
                if (value >= 32 && value <= 126) {
                    if (fputc((int)value, stdout) == EOF) {
                        return -1;
                    }
                } else {
                    if (fprintf(stdout, "\\x%02X", (unsigned int)value) < 0) {
                        return -1;
                    }
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

    return 0;
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

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            char *new_buffer;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *result = buffer;
    return 0;
}

int main(int argc, char *argv[])
{
    CharTuple *tuple;
    const char *input;
    char *input_buffer = NULL;

    if (argc == 2) {
        input = argv[1];
    } else if (argc == 1) {
        if (read_input_line(&input_buffer) != 0) {
            return EXIT_FAILURE;
        }
        input = input_buffer;
    } else {
        const char *program_name =
            argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    tuple = string_to_tuple(input);
    free(input_buffer);

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    if (print_tuple(tuple) != 0) {
        free_tuple(tuple);
        return EXIT_FAILURE;
    }

    free_tuple(tuple);
    return EXIT_SUCCESS;
}