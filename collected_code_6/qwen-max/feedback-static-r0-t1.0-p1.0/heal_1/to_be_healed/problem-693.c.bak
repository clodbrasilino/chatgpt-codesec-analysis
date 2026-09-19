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

    size_t nmatch = 10;
    regmatch_t pmatch[nmatch];
    int match_count;

    while ((match_count = regexec(&reg, str, nmatch, pmatch, 0)) == 0) {
        size_t length_before, replacement_length, to_be_replaced_length, remaining_length, total_length, new_length;
        length_before = pmatch[0].rm_so;
        replacement_length = strlen(replacement);
        to_be_replaced_length = pmatch[0].rm_eo - pmatch[0].rm_so;
        remaining_length = strlen(str + pmatch[0].rm_eo);
        /* Possible weaknesses found:
         *  Variable 'total_length' is assigned a value that is never used. [unreadVariable]
         */
        total_length = length_before + to_be_replaced_length + remaining_length;
        /* Possible weaknesses found:
         *  Variable 'new_length' is assigned a value that is never used. [unreadVariable]
         */
        new_length = length_before + replacement_length + remaining_length;

        memmove(str + length_before + replacement_length, str + pmatch[0].rm_eo, remaining_length + 1);
        strncpy(str + length_before, replacement, replacement_length);
    }

    /* Possible weaknesses found:
     *  Condition 'match_count!=0' is always true [knownConditionTrueFalse]
     */
    if (match_count != REG_NOMATCH && match_count != 0) {
        fprintf(stderr, "Matching error\n");
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     *  invalid operands to binary expression ('void' and 'int')
     *  void value not ignored as it ought to be
     */
    if (regfree(&reg) != 0) {
        fprintf(stderr, "Regex freeing failed\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char *input = strdup("This   is  an example   text  with  multiple   spaces.");
    remove_multiple_spaces(input);
    printf("%s\n", input);
    free(input);
    return 0;
}