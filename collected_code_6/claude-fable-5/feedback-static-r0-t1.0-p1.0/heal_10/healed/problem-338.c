#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 256U

long count_substrings(const char *str, size_t max_len)
{
    long count;
    size_t len;
    size_t i;
    size_t j;

    if (str == NULL) {
        return -1L;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1L;
    }

    count = 0L;

    for (i = 0U; i < len; i++) {
        for (j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];
    long result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    result = count_substrings(buffer, sizeof(buffer));
    if (result < 0L) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (printf("%ld\n", result) < 0) {
        return 1;
    }

    return 0;
}