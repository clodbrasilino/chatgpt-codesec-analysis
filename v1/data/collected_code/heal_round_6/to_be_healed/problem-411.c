#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 256

void snakeToCamel(char* snakeCase, char* camelCase, size_t maxStringLength) {
    regex_t regex;
    regmatch_t match;
    int currentIndex = 0;

    if (snakeCase == NULL || camelCase == NULL || maxStringLength == 0)
        return;

    size_t snakeLength = strnlen(snakeCase, maxStringLength);
    if(snakeLength >= maxStringLength)
        return;

    if(regcomp(&regex, "_[a-z]", REG_EXTENDED))
        return;
    
    while (regexec(&regex, &snakeCase[currentIndex], 1, &match, 0) == 0) {
        if(currentIndex + match.rm_so >= maxStringLength - 1)
            break;

        camelCase[match.rm_so + currentIndex + 1] = toupper(snakeCase[match.rm_so + 1 + currentIndex]);

        size_t length = strnlen(&snakeCase[match.rm_so + currentIndex], maxStringLength - currentIndex - match.rm_so);

        if (length + currentIndex + match.rm_eo + 1 >= maxStringLength)
            break;
            
        memmove(&snakeCase[match.rm_so + currentIndex], &snakeCase[match.rm_eo + currentIndex + 1], length);

        currentIndex += match.rm_eo;
        camelCase[currentIndex] = '\0';
    }

    regfree(&regex);
}

int main() {
    char* snakeCase = calloc(MAX_STRING_SIZE, sizeof(char));
    if(snakeCase == NULL) return 1;
    
    char* camelCase = calloc(MAX_STRING_SIZE, sizeof(char));
    if(camelCase == NULL) {
        free(snakeCase);
        return 1;
    }
        
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120). Risk is low because the source is a  constant string.
     */
    strncpy(snakeCase, "convert_snake_case", MAX_STRING_SIZE);
    snakeCase[MAX_STRING_SIZE-1] = '\0';

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(camelCase, snakeCase, MAX_STRING_SIZE);
    camelCase[MAX_STRING_SIZE-1] = '\0';

    snakeToCamel(snakeCase, camelCase, MAX_STRING_SIZE);

    printf("Camel case: %s\n", camelCase);

    free(snakeCase);
    free(camelCase);

    return 0;
}