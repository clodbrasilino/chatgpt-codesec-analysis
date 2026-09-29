#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 64
#define MAX_DISCARD 4096U

bool digit_frequency_valid(const char *number, size_t max_len)
{
    int counts[10] = {0};
    size_t i;
    size_t len;

    if (number == NULL || max_len == 0U) {
        return false;
    }

    len = strnlen(number, max_len);
    if (len == 0U || len >= max_len) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if (!isdigit((unsigned char)number[i])) {
            return false;
        }
        const int digit = number[i] - '0';
        if (digit < 0 || digit > 9) {
            return false;
        }
        counts[digit]++;
    }

    for (i = 0U; i < 10U; i++) {
        if (counts[i] > (int)i) {
            return false;
        }
    }

    return true;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < MAX_DISCARD);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    size_t len;

    memset(input, 0, sizeof(input));

    printf("Enter a number: ");
    fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    } else if (len == sizeof(input) - 1U) {
        discard_remaining_input();
    }

    if (digit_frequency_valid(input, sizeof(input))) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}