#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 256

bool first_last_equal(const char *str, size_t max_len)
{
    size_t len;

    if (str == NULL || max_len == 0) {
        return false;
    }

    len = strnlen(str, max_len);

    if (len == 0 || len == max_len) {
        return false;
    }

    return str[0] == str[len - 1];
}

static bool read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];

    printf("Enter a string: ");
    fflush(stdout);

    if (!read_line(buffer, sizeof(buffer))) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (first_last_equal(buffer, sizeof(buffer))) {
        printf("The first and last characters are equal.\n");
    } else {
        printf("The first and last characters are not equal.\n");
    }

    return EXIT_SUCCESS;
}