#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 128

bool is_decimal_precision_two(const char *str, size_t max_len)
{
    size_t len;
    size_t i = 0;
    size_t digits_before = 0;
    size_t digits_after = 0;
    bool dot_found = false;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len == max_len) {
        return false;
    }

    if (str[i] == '+' || str[i] == '-') {
        i++;
        if (i == len) {
            return false;
        }
    }

    for (; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            if (dot_found) {
                digits_after++;
            } else {
                digits_before++;
            }
        } else if (str[i] == '.') {
            if (dot_found) {
                return false;
            }
            dot_found = true;
        } else {
            return false;
        }
    }

    if (digits_before == 0) {
        return false;
    }

    if (dot_found && (digits_after == 0 || digits_after > 2)) {
        return false;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    size_t len;

    printf("Enter a number: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    if (is_decimal_precision_two(buffer, sizeof(buffer))) {
        printf("Valid decimal with precision of 2: %s\n", buffer);
    } else {
        printf("Invalid decimal with precision of 2: %s\n", buffer);
    }

    return 0;
}