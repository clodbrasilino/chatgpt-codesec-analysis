#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#define CHAR_SET_SIZE 256

char most_common_char(const char *str, size_t *out_count)
{
    size_t counts[CHAR_SET_SIZE] = {0};
    size_t i;
    size_t max_count;
    size_t max_index;

    if (out_count == NULL) {
        return '\0';
    }
    *out_count = 0;

    if (str == NULL || str[0] == '\0') {
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        counts[(unsigned char)str[i]]++;
    }

    max_count = 0;
    max_index = 0;
    for (i = 0; i < CHAR_SET_SIZE; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_index = i;
        }
    }

    *out_count = max_count;
    return (char)(unsigned char)max_index;
}

int main(void)
{
    const char *test_strings[] = {
        "hello world, this is a test string",
        "aabbcc",
        "",
        "programming"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        size_t count = 0;
        char result = most_common_char(test_strings[i], &count);

        if (count == 0) {
            printf("String %zu: empty or invalid input.\n", i + 1);
        } else if (isprint((unsigned char)result)) {
            printf("String %zu: most common character is '%c' with %zu occurrences.\n",
                   i + 1, result, count);
        } else {
            printf("String %zu: most common character is 0x%02X with %zu occurrences.\n",
                   i + 1, (unsigned char)result, count);
        }
    }

    if (most_common_char(NULL, NULL) == '\0') {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}