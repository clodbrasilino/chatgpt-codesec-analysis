#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 256

void add_spaces(char *str, size_t maximum_length) {
    if(str == NULL || str[0] == '\0' || maximum_length == 0) { 
        return; 
    }

    size_t str_len = strnlen(str, maximum_length); 

    if(str_len >= maximum_length) {
        return;
    } 

    regex_t regex; 
    if(regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return; 
    }

    char *result = (char *) calloc(2 * str_len + 1, sizeof(char)); 
    if(result == NULL) { 
        return;
    }
     
    size_t i = 0, j = 0;
    while (i < str_len && j < 2 * str_len) {
        if(regexec(&regex, str + i, 0, NULL, 0) == REG_NOMATCH) {
            result[j++] = str[i];
        } else {
            result[j++] = ' ';
            if(j < 2 * str_len) {
                result[j++] = str[i];
            }
        }
        i++;
    }

    result[strnlen(result, 2 * str_len)] = '\0'; 

    size_t copy_length = str_len - 1;
    if( copy_length > 2 * str_len)
        copy_length = 2 * str_len;
    memcpy(str, result, copy_length);
    str[copy_length] = '\0';

    free(result);
    regfree(&regex);
}

int main() {
    char str[MAX_SIZE] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str, MAX_SIZE - 1);
    printf("%s\n", str);

    return 0;
}