#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256

static int is_word_char(int c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static int word_has_inner_z(const char *word, size_t len)
{
    size_t i;

    if (word == NULL || len < 3U) {
        return 0;
    }

    for (i = 1U; i < len - 1U; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return 1;
        }
    }

    return 0;
}

int match_word_with_inner_z(const char *text, char *result, size_t result_size)
{
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    size_t start;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    size_t text_len;

    if (text == NULL || result == NULL || result_size == 0U) {
        return -1;
    }

    result[0] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    i = 0U;

    while (i < text_len) {
        while (i < text_len && !is_word_char((unsigned char)text[i])) {
            i++;
        }

        start = i;

        while (i < text_len && is_word_char((unsigned char)text[i])) {
            i++;
        }

        len = i - start;

        if (len > 0U && word_has_inner_z(&text[start], len)) {
            if (len >= result_size) {
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, &text[start], len);
            result[len] = '\0';
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const char *tests[] = {
        "the lazy dog jumped",
        "zebra runs fast",
        "jazz is nice",
        "amazing puzzle here",
        "no match at all",
        "buzz fizz quiz"
    };
    size_t num_tests;
    size_t i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_WORD_LEN];
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    num_tests = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < num_tests; i++) {
        status = match_word_with_inner_z(tests[i], result, sizeof(result));

        if (status == 1) {
            if (printf("Input: \"%s\" -> Match: \"%s\"\n", tests[i], result) < 0) {
                return EXIT_FAILURE;
            }
        } else if (status == 0) {
            if (printf("Input: \"%s\" -> No match\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Error processing input: \"%s\"\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}