#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void camelToSnake(char *str) {
    char pattern[] = "([A-Z])";
    char replacement[] = "_\\1";
    regex_t regex;

    if(regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed");
        /* Possible weaknesses found:
         *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        return;
    }

    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(str);
    if(length == (size_t)-1) {
        printf("Input string over-read error\n");
        return;
    }

    length += regerror(0, &regex, NULL, 0) + 1;  
    char *result = calloc(length, sizeof(char));

    if (result == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    regmatch_t match;
    int offset = 0;
    size_t i = 0;
    
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;

        if((i + start) > length) {
            printf("Buffer overflow error\n");
            return;
        }
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(result + i, str + offset, start);
        i += start;

        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        size_t replacement_length = strlen(replacement);
        if(replacement_length == (size_t)-1) {
            printf("Replacement string over-read error\n");
            return;
        }

        if((i + replacement_length) > length) {
            printf("Buffer overflow error\n");
            return;
        }
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(result + i, replacement, replacement_length);
        i += replacement_length;

        offset += end;
    }
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t remaining_length = strlen(str + offset);
    if(remaining_length == (size_t)-1) {
        printf("Input string over-read error\n");
        return;
    }

    if((i + remaining_length) > length) {
        printf("Buffer overflow error\n");
        return;
    }
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(result + i, str + offset, remaining_length);
    result[i + remaining_length] = '\0';
    
    printf("%s\n", result);
    
    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "camelCaseString";
    camelToSnake(input);

    return 0;
}