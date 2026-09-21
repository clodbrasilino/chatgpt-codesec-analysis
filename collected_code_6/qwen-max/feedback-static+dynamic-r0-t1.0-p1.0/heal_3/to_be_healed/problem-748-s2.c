#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_between_capital_words(char **str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti;
    char *ptr = *str;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(*str);
    char *new_str = (char *)malloc(len * 2 + 1);
    if (!new_str) return;
    int new_index = 0;

    if (regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED) != 0) {
        free(new_str);
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'reti' is used in the enclosing expression, the value is never actually read from 'reti' [deadcode.DeadStores]
     */
    while ((reti = regexec(&regex, ptr, 1, pmatch, 0)) == 0) {
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(ptr);
    if (remaining_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str + new_index, ptr, remaining_len);
        new_str[new_index + remaining_len] = '\0';
    } else {
        new_str[new_index] = '\0';
    }

    regfree(&regex);

    free(*str);
    *str = (char *)realloc(new_str, new_index + remaining_len + 1);
}

int main() {
    char *input = strdup("HelloWorldThisIsATest");
    add_spaces_between_capital_words(&input);
    printf("%s\n", input);
    free(input);
    return 0;
}