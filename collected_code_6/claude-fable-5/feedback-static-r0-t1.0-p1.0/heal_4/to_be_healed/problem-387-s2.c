#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 128

int is_valid_hex(const char *str);
int hex_is_even(const char *hex_str);
static int read_line(char *buf, size_t size);

int is_valid_hex(const char *str)
{
    size_t len;
    size_t i;
    size_t start = 0;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return 0;
    }

    if (len > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        start = 2;
    }

    if (start >= len) {
        return 0;
    }

    for (i = start; i < len; i++) {
        if (!isxdigit((unsigned char)str[i])) {
            return 0;
        }
    }

    return 1;
}

int hex_is_even(const char *hex_str)
{
    size_t len;
    char last;
    int digit_value;

    if (hex_str == NULL) {
        return 0;
    }

    len = strnlen(hex_str, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return 0;
    }

    last = hex_str[len - 1];

    if (last >= '0' && last <= '9') {
        digit_value = last - '0';
    } else if (last >= 'a' && last <= 'f') {
        digit_value = last - 'a' + 10;
    } else if (last >= 'A' && last <= 'F') {
        digit_value = last - 'A' + 10;
    } else {
        return 0;
    }

    return (digit_value % 2) == 0;
}

static int read_line(char *buf, size_t size)
{
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (buf == NULL || size == 0) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    buf[size - 1] = '\0';

    len = strnlen(buf, size);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return 0;
    }

    if (len == size - 1) {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return -2;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    int status;

    printf("Enter a hexadecimal number: ");

    status = read_line(buffer, sizeof(buffer));
    if (status == -1) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_hex(buffer)) {
        fprintf(stderr, "Invalid hexadecimal number\n");
        return EXIT_FAILURE;
    }

    if (hex_is_even(buffer)) {
        printf("%s is even\n", buffer);
    } else {
        printf("%s is odd\n", buffer);
    }

    return EXIT_SUCCESS;
}