#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_words(const char *input, int word_length) {
    char pattern[6];
    snprintf(pattern, sizeof(pattern), "\\b\\w{%d}\\b", word_length);
    regex_t regex;
    regmatch_t matches[1];

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    const size_t input_len = strlen(input);
    for (size_t i = 0; i <= input_len; i++) {
        if (regexec(&regex, &input[i], 1, matches, 0) == 0) {
            for (int k = matches[0].rm_so; k < matches[0].rm_eo; k++) {
                putchar(input[k]);
            }
            putchar('\n');
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