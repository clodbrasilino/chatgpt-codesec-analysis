#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TEXT_LEN 4096
#define RESULT_BUF_SIZE 256

int find_word_with_inner_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;
    size_t len;

    if (text == NULL || result == NULL || result_size == 0) {
        return 0;
    }

    result[0] = '\0';

    len = strnlen(text, MAX_TEXT_LEN);

    while (i < len) {
        while (i < len && !isalpha((unsigned char)text[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        size_t start = i;

        while (i < len && isalpha((unsigned char)text[i])) {
            i++;
        }

        size_t word_len = i - start;

        if (word_len >= 3) {
            size_t j;
            int found = 0;

            for (j = start + 1; j < i - 1; j++) {
                if (tolower((unsigned char)text[j]) == 'z') {
                    found = 1;
                    break;
                }
            }

            if (found) {
                if (word_len >= result_size) {
                    return 0;
                }
                for (j = 0; j < word_len; j++) {
                    result[j] = text[start + j];
                }
                result[word_len] = '\0';
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const char *tests[] = {
        "the amazing puzzle was solved",
        "zebra runs fast",
        "jazz music plays",
        "no match here",
        "a hazy day"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[RESULT_BUF_SIZE];

    memset(buffer, 0, sizeof(buffer));

    for (i = 0; i < count; i++) {
        if (find_word_with_inner_z(tests[i], buffer, sizeof(buffer))) {
            if (printf("Input: \"%s\" -> Match: \"%s\"\n", tests[i], buffer) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Input: \"%s\" -> No match\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}