#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MONTH_BUFFER_SIZE 32U

static int equals_ignore_case(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;

        if (tolower(first_char) != tolower(second_char)) {
            return 0;
        }

        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

static int month_has_31_days(const char *month)
{
    static const char *const months[] = {
        "January",
        "March",
        "May",
        "July",
        "August",
        "October",
        "December"
    };
    size_t i;

    for (i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int read_month(char *buffer, size_t capacity)
{
    int character;
    size_t length = 0U;
    int too_long = 0;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length + 1U < capacity) {
            buffer[length++] = (char)character;
        } else {
            too_long = 1;
        }
    }

    buffer[length] = '\0';

    if (ferror(stdin)) {
        return 0;
    }

    if (too_long) {
        buffer[0] = '\0';
        return -1;
    }

    return length == 0U ? 0 : 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE] = {0};
    int status = read_month(month, sizeof month);

    if (status < 0) {
        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    if (status == 0) {
        if (ferror(stdin)) {
            fputs("Failed to read the month name.\n", stderr);
        } else {
            fputs("Month name cannot be empty.\n", stderr);
        }
        return 1;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    return 0;
}