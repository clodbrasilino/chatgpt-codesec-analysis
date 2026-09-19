#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  The scope of the variable 'match_len' can be reduced. [variableScope]
     */
    int match_len;
    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        /* Possible weaknesses found:
         *  Value stored to 'match_len' is never read [deadcode.DeadStores]
         *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
         */
        match_len = end - start;
        memmove(str + start, str + end, strlen(str + end) + 1);
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt sTrInG wItH lOwErCaSe ChArAcTeRs.";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}