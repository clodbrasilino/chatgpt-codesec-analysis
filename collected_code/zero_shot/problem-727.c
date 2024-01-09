#include <stdio.h>
#include <regex.h>
#include <string.h>

void removeSpecialCharacters(char* str) {
    regex_t regex;
    int ret;

    // Compile the regular expression pattern
    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    // Execute the regular expression
    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret) {
        // If a match is found, replace special characters with empty string
        regfree(&regex);
        regex_t regex2;
        ret = regcomp(&regex2, "[^a-zA-Z0-9]", REG_EXTENDED);
        char* result = (char*)malloc(sizeof(char) * (strlen(str) + 1));
        regmatch_t pmatch;
        int index = 0;

        while (regexec(&regex2, str + index, 1, &pmatch, 0) == 0) {
            strncpy(result + index, str + index + pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
            index += pmatch.rm_eo - pmatch.rm_so;
        }
        
        strncpy(result + index, str + index + pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
        strcpy(str, result);
        free(result);
        regfree(&regex2);
    }
    
    regfree(&regex);
}

int main() {
    char str[100] = "Hello! How are you? 123";
    removeSpecialCharacters(str);
    printf("%s\n", str);
    return 0;
}