#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void camelToSnake(char *str) {
    char pattern[] = "([A-Z])";
    char replacement[] = "_\\1";
    regex_t regex;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed");
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = str != NULL ? strlen(str) + 1 : 0;

    if (length == 0) {
        printf("Non-\0-terminated strings are not allowed\n");
        return;
    }
    
    length += regerror(0, &regex, NULL, 0) + 1;

    char *result = malloc(length);
    
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    regmatch_t match;
    int offset = 0;
    int i = 0;
    
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        int matchedLength = end - start;
        
        snprintf(result + i, length - i, "%.*s", start, str + offset);
        i += start;

        snprintf(result + i, length - i, "%s", replacement);
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        i += strlen(replacement);

        offset += end;
    }
    
    snprintf(result + i, length - i, "%s", str + offset);

    printf("%s\n", result);
    
    free(result);
    regfree(&regex);
}

int main() {
    char input[] = "camelCaseString";
    camelToSnake(input);
    
    return 0;
}