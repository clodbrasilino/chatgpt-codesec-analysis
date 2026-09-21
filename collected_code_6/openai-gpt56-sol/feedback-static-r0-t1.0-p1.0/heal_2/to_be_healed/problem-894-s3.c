#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *values;
    size_t size;
} FloatTuple;

static void free_float_tuple(FloatTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->size = 0U;
    }
}

static int string_to_float_tuple(const char *input, FloatTuple *tuple)
{
    const char *cursor;
    float *values = NULL;
    size_t count = 0U;
    size_t capacity = 0U;

    if (input == NULL || tuple == NULL) {
        return 0;
    }

    tuple->values = NULL;
    tuple->size = 0U;
    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '(') {
        return 0;
    }
    ++cursor;

    for (;;) {
        char *end;
        float value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ')') {
            ++cursor;
            break;
        }

        errno = 0;
        value = strtof(cursor, &end);
        if (end == cursor || errno == ERANGE) {
            free(values);
            return 0;
        }
        cursor = end;

        if (count == capacity) {
            size_t new_capacity;
            float *new_values;

            if (capacity == 0U) {
                new_capacity = 4U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(values);
                    return 0;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX / sizeof(*values)) {
                free(values);
                return 0;
            }

            new_values = realloc(values, new_capacity * sizeof(*values));
            if (new_values == NULL) {
                free(values);
                return 0;
            }

            values = new_values;
            capacity = new_capacity;
        }

        values[count++] = value;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == ',') {
            ++cursor;

            while (isspace((unsigned char)*cursor)) {
                ++cursor;
            }

            if (*cursor == ')' || *cursor == '\0') {
                free(values);
                return 0;
            }
        } else if (*cursor != ')') {
            free(values);
            return 0;
        }
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(values);
        return 0;
    }

    tuple->values = values;
    tuple->size = count;
    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == capacity) {
            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > (SIZE_MAX - 1U) / 2U) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2U;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0U)) {
        free(buffer);
        return NULL;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return NULL;
    }

    if (capacity <= length) {
        char *new_buffer = realloc(buffer, length + 1U);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    FloatTuple tuple = { NULL, 0U };
    size_t i;

    input = read_line(stdin);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (!string_to_float_tuple(input, &tuple)) {
        free(input);
        fputs("Invalid float tuple\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    putchar('(');
    for (i = 0U; i < tuple.size; ++i) {
        if (i != 0U) {
            fputs(", ", stdout);
        }
        printf("%.9g", (double)tuple.values[i]);
    }
    puts(")");

    free_float_tuple(&tuple);
    return EXIT_SUCCESS;
}