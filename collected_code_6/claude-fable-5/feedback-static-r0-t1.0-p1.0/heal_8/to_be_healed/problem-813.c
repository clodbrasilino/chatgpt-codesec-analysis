#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 256

static size_t string_length(const char *str, size_t max_len)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (length < max_len && str[length] != '\0') {
        length++;
    }

    return length;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0;
    const size_t guard_max = 1000000;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < guard_max);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT] = {0};
    size_t length;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    length = string_length(buffer, sizeof(buffer));

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        length--;
        printf("You entered: %s\n", buffer);
    } else if (length == sizeof(buffer) - 1) {
        flush_stdin();
        printf("You entered (truncated): %s\n", buffer);
    } else {
        printf("You entered: %s\n", buffer);
    }

    printf("Length of the string: %zu\n", length);

    return EXIT_SUCCESS;
}