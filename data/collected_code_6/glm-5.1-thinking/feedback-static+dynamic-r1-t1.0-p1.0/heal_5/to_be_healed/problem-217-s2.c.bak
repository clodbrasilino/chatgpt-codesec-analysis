#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef EINVAL
#define EINVAL 22
#endif

int find_first_repeated(const char *str) {
    if (str == NULL) {
        errno = EINVAL;
        return -1;
    }

    int seen[256] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
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
    int result;

    result = find_first_repeated(test1);
    if (result != -1) {
        printf("%c\n", (char)result);
    } else {
        printf("No repeated character\n");
    }

    result = find_first_repeated(test2);
    if (result != -1) {
        printf("%c\n", (char)result);
    } else {
        printf("No repeated character\n");
    }

    errno = 0;
    /* Possible weaknesses found:
     *  Assignment 'result=find_first_repeated(NULL)', assigned value is -1
     *  Calling function 'find_first_repeated' returns -1
     */
    result = find_first_repeated(NULL);
    if (errno == EINVAL) {
        printf("Invalid input\n");
    /* Possible weaknesses found:
     *  Condition 'result!=-1' is always false
     *  Condition 'result!=-1' is always false [knownConditionTrueFalse]
     */
    } else if (result != -1) {
        printf("%c\n", (char)result);
    } else {
        printf("No repeated character\n");
    }

    return 0;
}