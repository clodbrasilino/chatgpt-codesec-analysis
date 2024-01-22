#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_SIZE 256

void add_spaces(char *str, size_t maximum_length) {
    if(str == NULL || str[0] == '\0')
        return;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t str_len = strlen(str);
    if(str_len >= maximum_length)
        return;

    regex_t regex;
    if(regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0)
        return;

    char *result = (char *) calloc(2 * str_len + 1, sizeof(char));
    if(result == NULL)
        return;

    size_t i = 0, j = 0;
    while (i < str_len) {
        if (regexec(&regex, str + i, 0, NULL, 0) == REG_NOMATCH) {
            result[j++] = str[i];
        } else {
            result[j++] = ' ';
            result[j++] = str[i];
        }
        i++;
        if(j >= maximum_length - 1)
            break;
    }
    result[j] = '\0';

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(strlen(result) != 0) {
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(str, result, maximum_length);
        str[maximum_length - 1] = '\0'; 
    }

    free(result);
    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str, MAX_SIZE);
    printf("%s\n", str);
    return 0;
}
