#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char first_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    bool seen[256] = {false};
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return str[i];
        }
        seen[c] = true;
    }

    return '\0';
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "abcdef";
    const char *test3 = "aabbcc";
    const char *test4 = "";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;

    char result;

    result = first_repeated_char(test1);
    printf("First repeated in \"%s\": %c\n", test1, result ? result : '-');

    result = first_repeated_char(test2);
    printf("First repeated in \"%s\": %c\n", test2, result ? result : '-');

    result = first_repeated_char(test3);
    printf("First repeated in \"%s\": %c\n", test3, result ? result : '-');

    result = first_repeated_char(test4);
    printf("First repeated in \"%s\": %c\n", test4, result ? result : '-');

    /* Possible weaknesses found:
     *  Condition 'test5==NULL' is always true
     *  Condition 'test5==NULL' is always true [knownConditionTrueFalse]
     */
    if (test5 == NULL) {
        printf("First repeated in NULL: -\n");
    } else {
        result = first_repeated_char(test5);
        if (result == '\0') {
            printf("First repeated in NULL: -\n");
        } else {
            printf("First repeated in NULL: %c\n", result);
        }
    }

    return 0;
}