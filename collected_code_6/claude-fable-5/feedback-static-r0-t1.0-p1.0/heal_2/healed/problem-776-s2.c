#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

static int is_vowel(char c)
{
    char lower = (char)tolower((unsigned char)c);
    return (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u');
}

int count_chars_with_vowel_neighbors(const char *str)
{
    size_t len;
    size_t i;
    int count = 0;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return -1;
    }

    if (len < 2U) {
        return 0;
    }

    for (i = 0U; i < len; i++) {
        int has_vowel_neighbor = 0;

        if (i > 0U && is_vowel(str[i - 1U])) {
            has_vowel_neighbor = 1;
        }
        if (i < (len - 1U) && is_vowel(str[i + 1U])) {
            has_vowel_neighbor = 1;
        }
        if (has_vowel_neighbor) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *tests[] = {
        "bestinstareels",
        "partofthejourneyistheend",
        "amazonprime"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < num_tests; i++) {
        int result = count_chars_with_vowel_neighbors(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error: invalid input\n");
            return EXIT_FAILURE;
        }
        printf("Count for \"%s\": %d\n", tests[i], result);
    }

    return EXIT_SUCCESS;
}