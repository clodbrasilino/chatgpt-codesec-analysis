#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_WORD_LENGTH 256

void findLongWords(const char *str) {
    regex_t regex;
    regmatch_t matches[1];

    if (regcomp(&regex, "\\b\\w{4,}\\b", REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return;
    }

    const char *cur_str = str;
    while (regexec(&regex, cur_str, 1, matches, 0) == 0) {
        char word[MAX_WORD_LENGTH];
        int length = matches[0].rm_eo - matches[0].rm_so;

        if(length < MAX_WORD_LENGTH) {
            strncpy(word, &cur_str[matches[0].rm_so], length);
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