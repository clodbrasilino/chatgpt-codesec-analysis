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

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
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
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 */
                memcpy(result+index, str+index+pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
                index += pmatch.rm_eo - pmatch.rm_so;
            } else {
                break;
            }
        }

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if((strSize)>=strlen(result)) {
            /* Possible weaknesses found:
             *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            memcpy(str, result, strlen(result));
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            str[strlen(result)] = '\0';
        }

        free(result);
        regfree(&regex2);
    }
    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100] = "Hello! How are you? 123";
    removeSpecialCharacters(str);
    printf("%s\n", str);
    return 0;
}