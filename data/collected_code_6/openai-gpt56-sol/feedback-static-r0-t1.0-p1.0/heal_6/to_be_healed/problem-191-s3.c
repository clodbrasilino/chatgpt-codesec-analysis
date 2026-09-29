#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MONTH_BUFFER_SIZE 32U

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

    const size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0U; i < count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int discard_line(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n') {
        if (character == EOF) {
            return ferror(stdin) == 0;
        }
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32] = {0};

    if (fgets(month, sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    const char *terminator = memchr(month, '\0', sizeof(month));
    if (terminator == NULL) {
        fputs("Invalid input.\n", stderr);
        return 1;
    }

    size_t length = (size_t)(terminator - month);

    if (length > 0U && month[length - 1U] == '\n') {
        month[--length] = '\0';

        if (length > 0U && month[length - 1U] == '\r') {
            month[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        if (!discard_line()) {
            fputs("Failed to read the month.\n", stderr);
            return 1;
        }

        fputs("Month name is too long.\n", stderr);
        return 1;
    }

    if (length == 0U) {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    return 0;
}