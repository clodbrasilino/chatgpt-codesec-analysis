#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} Tuple;

static void tuple_free(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
    tuple->capacity = 0;
}

static bool tuple_append(Tuple *tuple, char *item)
{
    const size_t maximum = SIZE_MAX / sizeof(*tuple->items);

    if (tuple->count == tuple->capacity) {
        size_t new_capacity;
        char **new_items;

        if (tuple->capacity >= maximum) {
            return false;
        }

        if (tuple->capacity == 0) {
            new_capacity = maximum < 4 ? maximum : 4;
        } else if (tuple->capacity > maximum / 2) {
            new_capacity = maximum;
        } else {
            new_capacity = tuple->capacity * 2;
        }

        new_items = realloc(tuple->items,
                            new_capacity * sizeof(*tuple->items));
        if (new_items == NULL) {
            return false;
        }

        tuple->items = new_items;
        tuple->capacity = new_capacity;
    }

    tuple->items[tuple->count++] = item;
    return true;
}

static char *copy_slice(const char *begin, const char *end)
{
    size_t length;
    char *copy;

    if (begin == NULL || end == NULL || end < begin) {
        return NULL;
    }

    length = (size_t)(end - begin);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, begin, length);
    }

    copy[length] = '\0';
    return copy;
}

static char decode_escape(char character)
{
    switch (character) {
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        default:
            return character;
    }
}

bool string_to_tuple(const char *input, Tuple *result)
{
    const char *begin;
    const char *end;
    const char *current;

    if (input == NULL || result == NULL) {
        return false;
    }

    result->items = NULL;
    result->count = 0;
    result->capacity = 0;

    begin = input;
    end = input + strlen(input);

    while (begin < end && isspace((unsigned char)*begin)) {
        ++begin;
    }

    while (end > begin && isspace((unsigned char)end[-1])) {
        --end;
    }

    if (begin < end && (begin[0] == '(' || end[-1] == ')')) {
        if (begin[0] != '(' || end[-1] != ')') {
            return false;
        }

        ++begin;
        --end;

        while (begin < end && isspace((unsigned char)*begin)) {
            ++begin;
        }

        while (end > begin && isspace((unsigned char)end[-1])) {
            --end;
        }
    }

    if (begin == end) {
        return true;
    }

    current = begin;

    for (;;) {
        char *item;

        while (current < end && isspace((unsigned char)*current)) {
            ++current;
        }

        if (current < end && (*current == '"' || *current == '\'')) {
            const char quote = *current++;
            const size_t maximum_length = (size_t)(end - current);
            size_t length = 0;
            bool closed = false;

            if (maximum_length == SIZE_MAX) {
                tuple_free(result);
                return false;
            }

            item = malloc(maximum_length + 1);
            if (item == NULL) {
                tuple_free(result);
                return false;
            }

            while (current < end) {
                char character = *current++;

                if (character == quote) {
                    closed = true;
                    break;
                }

                if (character == '\\') {
                    if (current == end) {
                        free(item);
                        tuple_free(result);
                        return false;
                    }

                    character = decode_escape(*current++);
                }

                item[length++] = character;
            }

            if (!closed) {
                free(item);
                tuple_free(result);
                return false;
            }

            item[length] = '\0';

            while (current < end && isspace((unsigned char)*current)) {
                ++current;
            }

            if (current < end && *current != ',') {
                free(item);
                tuple_free(result);
                return false;
            }
        } else {
            const char *item_begin = current;
            const char *item_end;

            while (current < end && *current != ',') {
                ++current;
            }

            item_end = current;

            while (item_end > item_begin &&
                   isspace((unsigned char)item_end[-1])) {
                --item_end;
            }

            item = copy_slice(item_begin, item_end);
            if (item == NULL) {
                tuple_free(result);
                return false;
            }
        }

        if (!tuple_append(result, item)) {
            free(item);
            tuple_free(result);
            return false;
        }

        if (current == end) {
            break;
        }

        ++current;

        if (current == end) {
            item = copy_slice(end, end);

            if (item == NULL || !tuple_append(result, item)) {
                free(item);
                tuple_free(result);
                return false;
            }

            break;
        }
    }

    return true;
}

static bool print_quoted(const char *text)
{
    const unsigned char *current = (const unsigned char *)text;

    if (fputc('"', stdout) == EOF) {
        return false;
    }

    while (*current != '\0') {
        switch (*current) {
            case '\\':
                if (fputs("\\\\", stdout) == EOF) {
                    return false;
                }
                break;

            case '"':
                if (fputs("\\\"", stdout) == EOF) {
                    return false;
                }
                break;

            case '\n':
                if (fputs("\\n", stdout) == EOF) {
                    return false;
                }
                break;

            case '\r':
                if (fputs("\\r", stdout) == EOF) {
                    return false;
                }
                break;

            case '\t':
                if (fputs("\\t", stdout) == EOF) {
                    return false;
                }
                break;

            default:
                if (isprint(*current)) {
                    if (fputc(*current, stdout) == EOF) {
                        return false;
                    }
                } else if (fprintf(stdout, "\\x%02X", *current) < 0) {
                    return false;
                }
                break;
        }

        ++current;
    }

    return fputc('"', stdout) != EOF;
}

static bool tuple_print(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL || fputc('(', stdout) == EOF) {
        return false;
    }

    for (i = 0; i < tuple->count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (!print_quoted(tuple->items[i])) {
            return false;
        }
    }

    if (tuple->count == 1 && fputc(',', stdout) == EOF) {
        return false;
    }

    return fputs(")\n", stdout) != EOF;
}

int main(int argc, char *const argv[])
{
    Tuple tuple;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"(item1, item2, ...)\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!string_to_tuple(argv[1], &tuple)) {
        fputs("Invalid tuple or insufficient memory\n", stderr);
        return EXIT_FAILURE;
    }

    if (!tuple_print(&tuple)) {
        tuple_free(&tuple);
        return EXIT_FAILURE;
    }

    tuple_free(&tuple);
    return EXIT_SUCCESS;
}