#include <stdio.h>
#include <string.h>

char find_first_repeated(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int seen[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] == 1) {
            return str[i];
        }
        seen[c] = 1;
    }

    return '\0';
}

int main(void) {
    const char *test1 = "programming";
    const char *test2 = "abcdef";
    const char *test3 = NULL;

    char result;

    result = find_first_repeated(test1);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    result = find_first_repeated(test2);
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated' returns 0
     *  Assignment 'result=find_first_repeated(test3)', assigned value is 0
     */
    result = find_first_repeated(test3);
    /* Possible weaknesses found:
     *  Condition 'result!='\0'' is always false [knownConditionTrueFalse]
     *  Condition 'result!='\0'' is always false
     */
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    return 0;
}