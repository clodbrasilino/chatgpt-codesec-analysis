#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char *items;
    size_t length;
} CharTuple;

static size_t argument_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

CharTuple *string_to_tuple(const char *string, size_t length)
{
    CharTuple *tuple;
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    size_t index;

    if (string == NULL) {
        return NULL;
    }

    tuple = malloc(sizeof *tuple);
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->length = length;

    if (length != 0) {
        tuple->items = malloc(length * sizeof *tuple->items);
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }

        for (index = 0; index < length; ++index) {
            tuple->items[index] = (unsigned char)string[index];
        }
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

    if (tuple == NULL || (tuple->length != 0 && tuple->items == NULL)) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (index = 0; index < tuple->length; ++index) {
        unsigned char value = tuple->items[index];

        if (index != 0 && fputs(", ", stdout) == EOF) {
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
                } else if (fprintf(stdout, "\\x%02X", (unsigned int)value) < 0) {
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

    return 0;
}

int main(int argc, char *argv[])
{
    CharTuple *tuple;
    const char *program_name;
    size_t length;
    int result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    length = argument_length(argv[1]);
    tuple = string_to_tuple(argv[1], length);

    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    result = print_tuple(tuple);
    free_tuple(tuple);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}