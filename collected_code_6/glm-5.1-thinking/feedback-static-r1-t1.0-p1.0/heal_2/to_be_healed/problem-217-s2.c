#include <stdio.h>
#include <string.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int seen[256] = {0};
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] == 1) {
            return (int)c;
        }
        seen[c] = 1;
    }

    return -1;
}

int main(void) {
    const char *test1 = "programming";
    const char *test2 = "abcdef";
    const char *test3 = NULL;

    int result;

    result = find_first_repeated(test1);
    if (result != -1) {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    result = find_first_repeated(test2);
    if (result != -1) {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'result=find_first_repeated(test3)', assigned value is -1
     *  Calling function 'find_first_repeated' returns -1
     */
    result = find_first_repeated(test3);
    /* Possible weaknesses found:
     *  Condition 'result!=-1' is always false [knownConditionTrueFalse]
     *  Condition 'result!=-1' is always false
     */
    if (result != -1) {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    return 0;
}