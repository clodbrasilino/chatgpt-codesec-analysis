#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_words(const char *input, int word_length) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[12];
    snprintf(pattern, sizeof(pattern), "\\b\\w{%d}\\b", word_length);
    if (snprintf(NULL, 0, "\\b\\w{%d}\\b", word_length) >= sizeof(pattern)) {
        return;
    }
    regex_t regex;
    regmatch_t matches[100];

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  input_len is assigned 'strlen(input)' here.
     *  Return index of string to the first element that is 0
     */
    const size_t input_len = strlen(input);
    /* Possible weaknesses found:
     *  Condition 'input[input_len]!='\0'' is always false
     *  Condition 'input[input_len]!='\0'' is always false [knownConditionTrueFalse]
     */
    if (input[input_len] != '\0') {
        return;
    }
    for (size_t i = 0; i <= input_len - word_length; i++) {
        if (regexec(&regex, &input[i], 1, matches, 0) == 0) {
            for (int j = 0; j < 1 && matches[j].rm_so >= 0; j++) {
                for (int k = matches[j].rm_so + i; k < matches[j].rm_eo + i; k++) {
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