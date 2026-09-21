#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *str) {
    regex_t reg;
    const char *pattern = "\\s+";
    const char *replacement = " ";

    if (regcomp(&reg, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t nmatch = 1;
    regmatch_t pmatch[nmatch];
    int match_count;

    /* Possible weaknesses found:
     *  Although the value stored to 'match_count' is used in the enclosing expression, the value is never actually read from 'match_count' [deadcode.DeadStores]
     */
    while ((match_count = regexec(&reg, str, nmatch, pmatch, 0)) == 0) {
        size_t length_before = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t replacement_length = strlen(replacement);
        /* Possible weaknesses found:
         *  Value stored to 'to_be_replaced_length' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'to_be_replaced_length' is assigned a value that is never used. [unreadVariable]
         */
        size_t to_be_replaced_length = pmatch[0].rm_eo - pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_length = strlen(str + pmatch[0].rm_eo);

        memmove(str + length_before + replacement_length, str + pmatch[0].rm_eo, remaining_length + 1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + length_before, replacement, replacement_length);
    }

    regfree(&reg);
}

int main() {
    char *input = strdup("This   is  an example   text  with  multiple   spaces.");
    remove_multiple_spaces(input);
    printf("%s\n", input);
    free(input);
    return 0;
}