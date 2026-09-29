#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

static int count_integers(const int *list, size_t length, size_t *count)
{
    if (count == NULL || (list == NULL && length != 0U)) {
        return -1;
    }

    *count = length;
    return 0;
}

int main(void)
{
    int *list = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    size_t count = 0U;
    char *line = NULL;
    size_t line_capacity = 0U;
    int status = EXIT_FAILURE;

    for (;;) {
        size_t line_length = 0U;
        int ch;

        while ((ch = fgetc(stdin)) != EOF) {
            char *temporary;
            size_t new_capacity;

            if (line_length + 1U >= line_capacity) {
                if (line_capacity == 0U) {
                    new_capacity = 256U;
                } else {
                    if (line_capacity > SIZE_MAX / 2U) {
                        goto cleanup;
                    }
                    new_capacity = line_capacity * 2U;
                }

                temporary = realloc(line, new_capacity);
                if (temporary == NULL) {
                    goto cleanup;
                }

                line = temporary;
                line_capacity = new_capacity;
            }

            if (ch == '\n') {
                break;
            }

            line[line_length++] = (char)ch;
        }

        if (ch == EOF && ferror(stdin)) {
            goto cleanup;
        }

        if (line_length == 0U && ch == EOF) {
            break;
        }

        if (line_length + 1U > line_capacity) {
            char *temporary;

            if (line_length == SIZE_MAX) {
                goto cleanup;
            }

            temporary = realloc(line, line_length + 1U);
            if (temporary == NULL) {
                goto cleanup;
            }

            line = temporary;
            line_capacity = line_length + 1U;
        }

        line[line_length] = '\0';

        {
            char *cursor = line;

            while (*cursor != '\0') {
                char *end;
                long value;

                while (isspace((unsigned char)*cursor)) {
                    ++cursor;
                }

                if (*cursor == '\0') {
                    break;
                }

                errno = 0;
                value = strtol(cursor, &end, 10);

                if (end == cursor ||
                    errno == ERANGE ||
                    value < INT_MIN ||
                    value > INT_MAX) {
                    goto cleanup;
                }

                if (*end != '\0' && !isspace((unsigned char)*end)) {
                    goto cleanup;
                }

                if (length == capacity) {
                    size_t new_capacity;
                    int *temporary;

                    if (capacity == 0U) {
                        new_capacity = 8U;
                    } else {
                        if (capacity > SIZE_MAX / 2U) {
                            goto cleanup;
                        }
                        new_capacity = capacity * 2U;
                    }

                    if (new_capacity > SIZE_MAX / sizeof *list) {
                        goto cleanup;
                    }

                    temporary = realloc(list, new_capacity * sizeof *list);
                    if (temporary == NULL) {
                        goto cleanup;
                    }

                    list = temporary;
                    capacity = new_capacity;
                }

                list[length++] = (int)value;
                cursor = end;
            }
        }

        if (ch == EOF) {
            break;
        }
    }

    if (count_integers(list, length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    free(list);
    return status;
}