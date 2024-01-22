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
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        len = strlen(str) + 1;
        
        char *new_str = malloc(len);
        if (new_str) {
            /* Possible weaknesses found:
             *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
             */
            memcpy(new_str, str, len);
            /* Possible weaknesses found:
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            new_str[len - 1] = '\0';

            while (regexec(&regex, new_str, nmatch, pmatch, 0) == 0) {
                memmove(&new_str[pmatch[0].rm_so + 1], &new_str[pmatch[0].rm_eo], len - pmatch[0].rm_eo);
                new_str[pmatch[0].rm_so] = replace[0];
                
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
                len = strlen(new_str) + 1;
            }

            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            if(strlen(new_str) < len){
                /* Possible weaknesses found:
                 *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
                strncpy(str, new_str, strlen(new_str) + 1);
                /* Possible weaknesses found:
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
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