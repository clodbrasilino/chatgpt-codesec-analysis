#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 101

void removeSpecialCharacters(char* str, size_t strSize) {
    if(str == NULL || strSize <= 0) {
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
        if (ret) {
            fprintf(stderr, "Could not compile regex\n");
            return;
        }

        char* result = (char*)calloc(strSize + 1, sizeof(char));

        if(result == NULL){
            return;
        }

        regmatch_t pmatch;
        int index = 0;

        while(regexec(&regex2, str + index, 1, &pmatch, 0) == 0){
            size_t len = pmatch.rm_eo - pmatch.rm_so;
            if (len >= 0 && len + index < strSize) {
                memcpy(result+index, str+index+pmatch.rm_so, len);
                index += len;
            } else {
                break;
            }
        }

        if(strSize >= strlen(result)) {
            memcpy(str, result, strlen(result) + 1);
        }

        free(result);
        regfree(&regex2);
    }
    regfree(&regex);
}

int main() {
    char str[MAX_BUFFER] = "Hello! How are you? 123";
    removeSpecialCharacters(str, strlen(str));
    printf("%s\n", str);
    return 0;
}