#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_WORD_LENGTH 256

void findLongWords(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int ret;

    ret = regcomp(&regex, "\\b\\w{4,}\\b", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex\n");
        return;
    }

    const char *cur_str = str;
    while (regexec(&regex, cur_str, 1, matches, 0) == 0) {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char word[MAX_WORD_LENGTH];
        int length = matches[0].rm_eo - matches[0].rm_so;

        if(length < MAX_WORD_LENGTH) {
            /* Possible weaknesses found:
             *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
             */
            memcpy(word, &cur_str[matches[0].rm_so], length);
            word[length] = '\0';
            printf("%s\n", word);
        }
        
        cur_str += matches[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    const char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    findLongWords(str);

    return 0;
}