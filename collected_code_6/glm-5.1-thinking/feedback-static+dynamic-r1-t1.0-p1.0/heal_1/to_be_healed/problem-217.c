#include <stdio.h>
#include <string.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int char_set[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] > 0) {
            return (int)c;
        }
        char_set[c]++;
    }

    return -1;
}

int main(void) {
    const char *test1 = "programming";
    const char *test2 = "abcdef";
    const char *test3 = "abba";

    int res1 = find_first_repeated(test1);
    int res2 = find_first_repeated(test2);
    int res3 = find_first_repeated(test3);
    /* Possible weaknesses found:
     *  Assignment 'res4=find_first_repeated(NULL)', assigned value is -1
     *  Calling function 'find_first_repeated' returns -1
     */
    int res4 = find_first_repeated(NULL);

    if (res1 != -1) {
        printf("%c\n", res1);
    } else {
        printf("No repeated character\n");
    }

    if (res2 != -1) {
        printf("%c\n", res2);
    } else {
        printf("No repeated character\n");
    }

    if (res3 != -1) {
        printf("%c\n", res3);
    } else {
        printf("No repeated character\n");
    }

    /* Possible weaknesses found:
     *  Condition 'res4!=-1' is always false
     *  Condition 'res4!=-1' is always false [knownConditionTrueFalse]
     */
    if (res4 != -1) {
        printf("%c\n", res4);
    } else {
        printf("No repeated character\n");
    }

    return 0;
}