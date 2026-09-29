#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    int character;
    bool too_long = false;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    *length = 0U;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                return -1;
            }

            break;
        }

        if (*length < capacity) {
            buffer[(*length)++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    if (character == EOF && *length == 0U && !too_long) {
        return 0;
    }

    return too_long ? -2 : 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length;
    int status = read_line(input, sizeof input, &length);

    if (status == 0) {
        return 1;
    }

    if (status == -2) {
        fputs("Input too long\n", stderr);
        return 1;
    }

    if (status < 0) {
        fputs("Input error\n", stderr);
        return 1;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");
    return 0;
}