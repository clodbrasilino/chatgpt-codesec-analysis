#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_chars(char *str) {
    const char *replace = ":";
    regex_t regex;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    regcomp(&regex, "[ ,.]", REG_EXTENDED);
    
    size_t len = 0;
    if (str) {
        len = strlen(str) + 1;
        
        char *new_str = malloc(len);
        if (new_str) {
            memcpy(new_str, str, len);
            new_str[len - 1] = '\0';

            while (regexec(&regex, new_str, nmatch, pmatch, 0) == 0) {
                memmove(&new_str[pmatch[0].rm_so + 1], &new_str[pmatch[0].rm_eo], len - pmatch[0].rm_eo);
                new_str[pmatch[0].rm_so] = replace[0];
                
                len = strlen(new_str) + 1;
            }

            if(strlen(new_str) < len){
                strncpy(str, new_str, strlen(new_str) + 1);
                str[strlen(new_str)] = '\0';
            }
            
            free(new_str);
            regfree(&regex);
        }
    }
}

int main() {
    char str[] = "This is a string, with spaces and commas.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}