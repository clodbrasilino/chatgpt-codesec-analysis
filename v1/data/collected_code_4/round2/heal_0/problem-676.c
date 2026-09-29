#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

char *remove_non_alphanumeric(char *str) {
    regex_t regex;
    int reti;
    char *new_str = NULL;
    size_t len = 0;
    
    reti = regcomp(&regex, "[^a-zA-Z0-9]", 0);
    
    if (reti) {
        printf("Could not compile regex\n");
        exit(1);
    }
    
    for (size_t i = 0; i < strlen(str); i++) {
        reti = regexec(&regex, &str[i], 0, NULL, 0);
        if (!reti) {
            continue;
        }
        
        char arr[2] = {str[i], '\0'};
        size_t curr_len = strlen(arr);
        
        char *tmp_str = realloc(new_str, len + curr_len + 1);
        if (!tmp_str) {
            regfree(&regex);
            free(new_str);
            printf("Could not allocate memory\n");
            exit(1);
        }
        
        new_str = tmp_str;
        strcpy(new_str + len, arr);
        len += curr_len;
    }
    
    regfree(&regex);
    return new_str;
}

int main() {
    char str[] = "He!!o W0r&d!";
    char *new_str = remove_non_alphanumeric(str);
    printf("Modified string: %s\n", new_str);
    free(new_str);
    return 0;
}