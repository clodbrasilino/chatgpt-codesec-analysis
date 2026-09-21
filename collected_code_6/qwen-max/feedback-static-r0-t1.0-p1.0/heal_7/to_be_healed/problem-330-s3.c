#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_words(const char *input, int word_length) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[16];
    snprintf(pattern, sizeof(pattern) - 1, "\\b\\w{%d}\\b", word_length);
    pattern[sizeof(pattern) - 1] = '\0';
    regex_t regex;
    regmatch_t matches[100];

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    size_t input_len = strnlen(input, 1000);
    for (size_t i = 0; i < input_len; i++) {
        if (regexec(&regex, &input[i], 1, matches, 0) == 0) {
            for (int j = 0; j < 1 && matches[j].rm_so >= 0; j++) {
                for (int k = matches[j].rm_so + i; k < matches[j].rm_eo + i && k < input_len; k++) {
                    putchar(input[k]);
                }
                putchar('\n');
            }
            i += matches[0].rm_eo - 1;
        }
    }

    regfree(&regex);
}

int main() {
    const char *input = "This is a test string with some words of three, four and five characters like apple, banana, cat, dog, elephant, frog, grape, hat, ice, jack, kiwi, lime, mango, nut, olive, pear, queen, raspberry, strawberry, tomato, up, vest, whale, xylotomus, yellow, zebra";
    find_words(input, 3);
    find_words(input, 4);
    find_words(input, 5);
    return 0;
}