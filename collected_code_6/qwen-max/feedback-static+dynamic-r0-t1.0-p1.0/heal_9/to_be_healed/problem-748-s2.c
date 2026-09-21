#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char **str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char *ptr = *str;
    size_t len = 0;
    for (char *s = *str; *s; s++) len++;
    char *new_str = (char *)malloc(len * 2 + 1);
    if (!new_str) return;
    int new_index = 0;

    if (regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED) != 0) {
        free(new_str);
        return;
    }

    while (regexec(&regex, ptr, 1, pmatch, 0) == 0) {
        if (pmatch[0].rm_so > 0) {
            for (int i = 0; i < pmatch[0].rm_so; i++) {
                new_str[new_index++] = *ptr++;
            }
            new_str[new_index++] = ' ';
        }
        for (int i = 0; i < pmatch[0].rm_eo - pmatch[0].rm_so; i++) {
            new_str[new_index++] = *ptr++;
        }
        ptr += pmatch[0].rm_eo - pmatch[0].rm_so;
    }

    size_t remaining_len = (*str + len) - ptr;
    if (remaining_len) {
        size_t to_copy = (new_index + remaining_len) <= (len * 2 + 1) ? remaining_len : (len * 2 + 1 - new_index - 1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str + new_index, ptr, to_copy);
        new_index += to_copy;
    }
    new_str[new_index] = '\0';

    regfree(&regex);

    free(*str);
    *str = (char *)realloc(new_str, new_index + 1);
}

int main() {
    char *input = strdup("HelloWorldThisIsATest");
    add_spaces_between_capital_words(&input);
    printf("%s\n", input);
    free(input);
    return 0;
}