#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void removeSpecialCharacters(char* str) {
    if(str == NULL) {
        return;
    }
    
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if(!ret){
        regfree(&regex);
        regex_t regex2;
        ret = regcomp(&regex2,"[^a-zA-Z0-9]", REG_EXTENDED);  

        size_t strSize = strlen(str);
        char* result = (char*)malloc(sizeof(char) * (strSize + 1));
       
        if(result == NULL){
            return;
        }

        memset(result, 0, sizeof(char) * (strSize + 1));
        regmatch_t pmatch;
        int index = 0;

        while(regexec(&regex2, str + index, 1, &pmatch, 0) == 0){
            if ((pmatch.rm_eo - pmatch.rm_so) >= 0) {
                memcpy(result+index, str+index+pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
                index += pmatch.rm_eo - pmatch.rm_so;
            } else {
                break;
            }
        }

        if((strSize)>=strlen(result)) {
            memcpy(str, result, strlen(result));
            str[strlen(result)] = '\0';
        }

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