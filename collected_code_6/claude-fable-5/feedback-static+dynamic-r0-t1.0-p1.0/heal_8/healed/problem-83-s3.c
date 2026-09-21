#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 256

char sum_of_chars(const char *str, size_t max_len)
{
    unsigned long sum = 0UL;
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0U) {
        return '\0';
    }

    len = 0U;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len == max_len) {
        return '\0';
    }

    for (i = 0U; i < len; i++) {
        sum += (unsigned long)(unsigned char)str[i];
    }

    return (char)((((sum % 26UL) + 26UL - ((unsigned long)'a' % 26UL)) % 26UL) + (unsigned long)'a');
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    char result;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }

    result = sum_of_chars(buffer, sizeof(buffer));

    if (result == '\0') {
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    if (printf("Resulting character: %c\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}