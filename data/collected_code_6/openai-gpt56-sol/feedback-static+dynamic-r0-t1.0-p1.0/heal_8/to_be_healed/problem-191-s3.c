#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MONTH_BUFFER_SIZE 32

static int equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return 0;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return 0;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };

    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int read_month(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    length = strnlen(buffer, capacity);

    if (length == capacity) {
        buffer[capacity - 1] = '\0';
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';

        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return -1;
        }

        return 1;
    }

    return length == 0 ? 2 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE] = {0};
    int result = read_month(month, sizeof(month));

    if (result == -1) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    if (result == 1) {
        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    if (result == 2) {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    return 0;
}