#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char *items;
    size_t length;
} CharTuple;

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
    /* Possible weaknesses found:
     *  The scope of the variable 'value' can be reduced. [variableScope]
     */
    unsigned char value;

    if (tuple == NULL || fputc('(', stdout) == EOF) {
        return -1;
    }

    for (index = 0; index < tuple->length; ++index) {
        if (index > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        value = tuple->items[index];

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
                    if (fputc(value, stdout) == EOF) {
                        return -1;
                    }
                } else if (fprintf(stdout, "\\x%02X", value) < 0) {
                    return -1;
                }
                break;
        }

        if (fputc('\'', stdout) == EOF) {
            return -1;
        }
    }

    if (tuple->length == 1 && fputc(',', stdout) == EOF) {
        return -1;
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    CharTuple *tuple;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    tuple = string_to_tuple(argv[1]);
    if (tuple == NULL) {
        if (fputs("Failed to create tuple\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (print_tuple(tuple) != 0) {
        free_tuple(tuple);
        return EXIT_FAILURE;
    }

    free_tuple(tuple);
    return EXIT_SUCCESS;
}