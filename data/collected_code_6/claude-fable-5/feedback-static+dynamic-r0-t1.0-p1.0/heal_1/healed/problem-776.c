#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 4096U

static bool is_vowel(char c)
{
    char lower = (char)tolower((unsigned char)c);
    return (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u');
}

int count_vowel_neighbors(const char *str)
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

    for (i = 0; i < len; i++) {
        bool has_vowel_neighbor = false;

        if (i > 0U && is_vowel(str[i - 1U])) {
            has_vowel_neighbor = true;
        }
        if (i < (len - 1U) && is_vowel(str[i + 1U])) {
            has_vowel_neighbor = true;
        }

        if (has_vowel_neighbor) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *test_strings[] = {
        "bestinstareels",
        "partofthejourneyistheend",
        "amazonprime",
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        int result = count_vowel_neighbors(test_strings[i]);

        if (result < 0) {
            if (fprintf(stderr, "Error: invalid input string\n") < 0) {
                return 1;
            }
        } else {
            if (printf("String: \"%s\" -> Count: %d\n",
                       test_strings[i], result) < 0) {
                return 1;
            }
        }
    }

    return 0;
}