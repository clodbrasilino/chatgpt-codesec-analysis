#include <stdio.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count[256] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
        if (count[c] > 1) {
            return (int)c;
        }
    }

    return -2;
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "abcdef";
    const char *test3 = "swiss";
    const char *test4 = "";
    const char *test5 = NULL;

    int res1 = find_first_repeated(test1);
    int res2 = find_first_repeated(test2);
    int res3 = find_first_repeated(test3);
    int res4 = find_first_repeated(test4);
    /* Possible weaknesses found:
     *  Assignment 'res5=find_first_repeated(test5)', assigned value is -1
     *  Calling function 'find_first_repeated' returns -1
     */
    int res5 = find_first_repeated(test5);

    printf("Test 1: %c\n", res1 >= 0 ? res1 : '-');
    printf("Test 2: %c\n", res2 >= 0 ? res2 : '-');
    printf("Test 3: %c\n", res3 >= 0 ? res3 : '-');
    printf("Test 4: %c\n", res4 >= 0 ? res4 : '-');
    /* Possible weaknesses found:
     *  Condition 'res5>=0' is always false
     *  Condition 'res5>=0' is always false [knownConditionTrueFalse]
     */
    printf("Test 5: %c\n", res5 >= 0 ? res5 : '-');

    return 0;
}