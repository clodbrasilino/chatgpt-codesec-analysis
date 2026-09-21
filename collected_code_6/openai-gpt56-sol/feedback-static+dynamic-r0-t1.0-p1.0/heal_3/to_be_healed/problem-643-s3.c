#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool matches_word(const char *word, size_t length)
{
    if (word == NULL || length < 3U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!isalpha((unsigned char)word[i])) {
            return false;
        }
    }

    for (size_t i = 1U; i + 1U < length; ++i) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_CAPACITY];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0U;
    while (length < sizeof word && word[length] != '\0' &&
           word[length] != '\n' && word[length] != '\r') {
        ++length;
    }

    if (word[length] == '\r') {
        if (length + 1U < sizeof word &&
            word[length + 1U] != '\n' &&
            word[length + 1U] != '\0') {
            return 1;
        }
    } else if (word[length] == '\0') {
        if (length == sizeof word - 1U) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                while (ch != '\n' && ch != EOF) {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = fgetc(stdin);
                }
                return 1;
            }

            if (ferror(stdin)) {
                return 1;
            }
        }
    }

    word[length] = '\0';

    if (printf("%s\n", matches_word(word, length) ? "match" : "no match") < 0) {
        return 1;
    }

    return 0;
}