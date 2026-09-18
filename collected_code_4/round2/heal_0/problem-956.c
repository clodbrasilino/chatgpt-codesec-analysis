#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

void split_string_on_uppercase(char* str){
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if(ret){
        printf("Could not compile regex\n");
        exit(1);
    }

    regmatch_t matches[1];
    char* next_str = str;
    
    printf("Substrings:\n");
    while(next_str){
        if(regexec(&regex, next_str, 1, matches, 0) == 0){
            int match_len = matches[0].rm_eo - matches[0].rm_so;
            char* substring = (char*)malloc(sizeof(char) * (match_len + 1));
            strncpy(substring, next_str, match_len);
            substring[match_len] = '\0';
            printf("%s\n", substring);

            next_str += matches[0].rm_eo;
        } else {
            printf("%s\n", next_str);
            next_str = 0;
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    split_string_on_uppercase(str);
    return 0;
}