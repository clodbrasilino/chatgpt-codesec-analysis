#include <ctype.h>
#include <stdio.h>

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
    const size_t month_count = sizeof(months) / sizeof(months[0]);

    if (month == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE];
    size_t length = 0U;
    int ch;

    if (fgets(month, (int)sizeof(month), stdin) == NULL) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    while (length < sizeof(month) && month[length] != '\0' &&
           month[length] != '\n') {
        ++length;
    }

    if (length < sizeof(month) && month[length] == '\n') {
        month[length] = '\0';
    } else if (length < sizeof(month) && month[length] == '\0') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Month name is too long.\n", stderr);
            return 1;
        }
    } else {
        fputs("Invalid input.\n", stderr);
        return 1;
    }

    if (length > 0U && month[length - 1U] == '\r') {
        month[--length] = '\0';
    }

    if (length == 0U) {
        fputs("Month name cannot be empty.\n", stderr);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    return 0;
}