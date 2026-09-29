#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void removeSpecialCharacters(char* str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        /* Possible weaknesses found:
         *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
         */
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
        char* result = (char*)malloc(sizeof(char) * (strlen(str) + 1));
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        memset(result, 0, sizeof(char) * (strlen(str) + 1));
        regmatch_t pmatch;
        int index = 0;

        while(regexec(&regex2, str + index, 1, &pmatch, 0) == 0){
            if ((result+index) != NULL  && (str+index+pmatch.rm_so) != NULL && (pmatch.rm_eo - pmatch.rm_so) >= 0)
                /* Possible weaknesses found:
                 *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
                 */
                strncpy(result+index, str+index+pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
            else
                break;

            index += pmatch.rm_eo - pmatch.rm_so;
        }

        if ((result+index) != NULL  && (str+index+pmatch.rm_so) != NULL && (pmatch.rm_eo - pmatch.rm_so) >= 0)
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(result + index, str + index + pmatch.rm_so, pmatch.rm_eo - pmatch.rm_so);
        else
            return;

        /* Possible weaknesses found:
         *  check of 'str' for NULL after already dereferencing it [-Wanalyzer-deref-before-check]
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if(str!=NULL && strlen(str)>=strlen(result) )
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            strncpy(str, result, strlen(result));
        else
            return;

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