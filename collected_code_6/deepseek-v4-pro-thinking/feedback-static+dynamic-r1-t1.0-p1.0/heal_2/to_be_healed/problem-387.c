#include <stdio.h>

int hex_is_even(const char *str, size_t len)
{
    size_t start = 0;
    size_t end = len;
    int last_value = 0;

    if (str == NULL) {
        return -1;
    }

    while (start < end &&
           (str[start] == ' ' || str[start] == '\t' ||
            str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    if (start < end && (str[start] == '+' || str[start] == '-')) {
        start++;
    }

    if (start + 1 < end && str[start] == '0' &&
        (str[start + 1] == 'x' || str[start + 1] == 'X')) {
        start += 2;
    }

    while (end > start &&
           (str[end - 1] == ' ' || str[end - 1] == '\t' ||
            str[end - 1] == '\n' || str[end - 1] == '\r')) {
        end--;
    }

    if (start == end) {
        return -1;
    }

    for (size_t i = start; i < end; i++) {
        char c = str[i];

        if (c >= '0' && c <= '9') {
            last_value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            last_value = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            last_value = c - 'A' + 10;
        } else {
            return -1;
        }
    }

    return last_value % 2 == 0 ? 1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t len = 0;
    int result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    for (len = 0; len < sizeof(input) && input[len] != '\0'; len++) {
    }

    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }

            printf("Invalid hexadecimal number\n");
            return 1;
        }
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    result = hex_is_even(input, len);

    if (result < 0) {
        printf("Invalid hexadecimal number\n");
    } else if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}