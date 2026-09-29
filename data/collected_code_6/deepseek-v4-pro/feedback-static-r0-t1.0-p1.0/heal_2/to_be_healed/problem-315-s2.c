#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int first_max_even_word(const char *str, char *result, size_t result_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_size==0' is not redundant
     */
    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    size_t max_len = 0;
    size_t max_word_start = 0;
    int found = 0;
    size_t i = 0;
    size_t word_start = 0;

    while (1) {
        if (str[i] == '\0' || isspace((unsigned char)str[i])) {
            size_t word_len = i - word_start;
            if (word_len > 0 && word_len % 2 == 0) {
                if (!found || word_len > max_len) {
                    max_len = word_len;
                    max_word_start = word_start;
                    found = 1;
                }
            }
            if (str[i] == '\0') {
                break;
            }
            word_start = i + 1;
        }
        i++;
    }

    if (!found) {
        /* Possible weaknesses found:
         *  Condition 'result_size>0' is always true [knownConditionTrueFalse]
         *  Condition 'result_size>0' is always true
         */
        if (result_size > 0) {
            result[0] = '\0';
        }
        return 0;
    }

    if (max_len >= result_size) {
        max_len = result_size - 1;
    }

    size_t copy_len = max_len < result_size ? max_len : result_size - 1;
    for (size_t j = 0; j < copy_len; j++) {
        result[j] = str[max_word_start + j];
    }
    result[copy_len] = '\0';

    return 1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[100];

    int ret = first_max_even_word(text, word, sizeof(word));

    if (ret == 1) {
        printf("First max even word: %s\n", word);
    } else if (ret == 0) {
        printf("No even word found.\n");
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}