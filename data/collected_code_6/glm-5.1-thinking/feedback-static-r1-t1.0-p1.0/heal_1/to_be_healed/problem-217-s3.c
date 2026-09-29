#include <stdio.h>

char find_first_repeated(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int count[256] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (count[c] > 1) {
            return str[i];
        }
    }

    return '\0';
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "abcdef";
    const char *test3 = "swiss";
    const char *test4 = "";
    const char *test5 = NULL;

    char res1 = find_first_repeated(test1);
    char res2 = find_first_repeated(test2);
    char res3 = find_first_repeated(test3);
    char res4 = find_first_repeated(test4);
    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated' returns 0
     *  Assignment 'res5=find_first_repeated(test5)', assigned value is 0
     */
    char res5 = find_first_repeated(test5);

    printf("Test 1: %c\n", res1 ? res1 : '-');
    printf("Test 2: %c\n", res2 ? res2 : '-');
    printf("Test 3: %c\n", res3 ? res3 : '-');
    printf("Test 4: %c\n", res4 ? res4 : '-');
    /* Possible weaknesses found:
     *  Condition 'res5' is always false [knownConditionTrueFalse]
     *  Condition 'res5' is always false
     */
    printf("Test 5: %c\n", res5 ? res5 : '-');

    return 0;
}