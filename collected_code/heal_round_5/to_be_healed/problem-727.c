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
                /* Possible weaknesses found:
                 *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
                 */
                memcpy(result+index, str+index+pmatch.rm_so, len);
                index += len;
            } else {
                break;
            }
        }

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if(strSize >= strlen(result)) {
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
             */
            memcpy(str, result, strlen(result) + 1);
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
    char str[MAX_BUFFER] = "Hello! How are you? 123";
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    removeSpecialCharacters(str, strlen(str));
    printf("%s\n", str);
    return 0;
}