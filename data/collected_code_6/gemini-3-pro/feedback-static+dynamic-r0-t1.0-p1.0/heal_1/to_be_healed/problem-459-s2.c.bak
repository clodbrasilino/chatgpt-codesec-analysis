#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    regmatch_t pmatch[1];

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         *  Value stored to 'match_len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
         */
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        size_t remaining_len = strlen(str) - pmatch[0].rm_eo;
        
        memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, remaining_len + 1);
    }

    regfree(&regex);
}

int main() {
    char str1[] = "hello WORLD this IS a TEST string";
    
    remove_uppercase_substrings(str1);
    
    printf("%s\n", str1);
    
    return 0;
}