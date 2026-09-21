#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128

static int hex_digit_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static int is_hex_even(const char *hex, size_t maxlen)
{
    size_t len;
    size_t i;
    size_t start = 0;
    int last;

    if (hex == NULL || maxlen == 0) {
        return -1;
    }

    len = strnlen(hex, maxlen);

    if (len == maxlen) {
        return -1;
    }

    if (len > 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        start = 2;
    }

    if (len - start == 0) {
        return -1;
    }

    for (i = start; i < len; i++) {
        if (hex_digit_value(hex[i]) < 0) {
            return -1;
        }
    }

    last = hex_digit_value(hex[len - 1]);
    return (last % 2 == 0) ? 1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    int result;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    printf("Enter a hexadecimal number: ");

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Error: input too long\n");
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    buffer[sizeof buffer - 1] = '\0';

    result = is_hex_even(buffer, sizeof buffer);

    if (result < 0) {
        fprintf(stderr, "Error: invalid hexadecimal number\n");
        return 1;
    }

    printf("The hexadecimal number is %s\n", result == 1 ? "even" : "odd");

    return 0;
}