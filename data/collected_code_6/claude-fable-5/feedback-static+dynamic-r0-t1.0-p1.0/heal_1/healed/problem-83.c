#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 4096

char get_char(const char *str, size_t max_len)
{
    unsigned long sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return '\0';
    }

    len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len == 0 || len >= max_len) {
        return '\0';
    }

    for (i = 0; i < len; i++) {
        sum += (unsigned long)(unsigned char)str[i];
    }

    return (char)((sum % 26UL) + (unsigned long)'a');
}

int main(void)
{
    const char *input = "abc";
    char result;

    result = get_char(input, MAX_INPUT_LEN);
    if (result == '\0') {
        fprintf(stderr, "Invalid input string\n");
        return EXIT_FAILURE;
    }

    if (printf("Result: %c\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}