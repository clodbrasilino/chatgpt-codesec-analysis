#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define BUFFER_SIZE 256U

static bool is_binary_string(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (max_len == 0U) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0U; (i < max_len) && (str[i] != '\0'); i++) {
        if ((str[i] != '0') && (str[i] != '1')) {
            return false;
        }
    }

    if (i >= max_len) {
        return false;
    }

    return true;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while ((ch != '\n') && (ch != EOF));
}

static bool read_line(char *buffer, size_t size)
{
    size_t len;

    if ((buffer == NULL) || (size < 2U) || (size > (size_t)INT_MAX)) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    } else if (len == (size - 1U)) {
        discard_remaining_input();
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];

    (void)memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    (void)fflush(stdout);

    if (!read_line(buffer, sizeof(buffer))) {
        (void)fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (is_binary_string(buffer, sizeof(buffer))) {
        printf("The string is a binary string\n");
    } else {
        printf("The string is not a binary string\n");
    }

    return 0;
}