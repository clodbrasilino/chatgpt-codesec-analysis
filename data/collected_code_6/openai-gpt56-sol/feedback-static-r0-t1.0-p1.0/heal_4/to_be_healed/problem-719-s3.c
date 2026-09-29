#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str++ != 'a') {
        return false;
    }

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF || ch == '\n' || ch == '\r') {
            if (ch == '\r') {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int next = fgetc(stream);
                if (next != '\n' && next != EOF) {
                    ungetc(next, stream);
                }
            }

            if (ch == EOF && length == 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
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

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    puts(matches_pattern(input) ? "Match" : "No match");
    free(input);

    return 0;
}