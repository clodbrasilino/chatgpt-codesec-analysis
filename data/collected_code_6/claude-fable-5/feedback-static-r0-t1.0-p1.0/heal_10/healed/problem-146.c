#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 256

long ascii_sum(const char *str, size_t max_len)
{
    long sum = 0;
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }

    return sum;
}

static int discard_remaining_input(void)
{
    int ch;
    size_t discarded = 0;
    const size_t discard_limit = 1048576;

    do {
        ch = getchar();
        discarded++;
        if (discarded > discard_limit) {
            return -1;
        }
    } while (ch != '\n' && ch != EOF);

    return (ch == EOF) ? EOF : 0;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    long result;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        if (discard_remaining_input() < 0) {
            fprintf(stderr, "Error discarding input\n");
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = ascii_sum(buffer, sizeof(buffer));
    if (result < 0) {
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    printf("Sum of ASCII values: %ld\n", result);

    return EXIT_SUCCESS;
}