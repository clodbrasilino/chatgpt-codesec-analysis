#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char findFirstRepeatedChar(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int count[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] == 1) {
            return str[i];
        }
        count[c]++;
    }

    return '\0';
}

int main(void) {
    const char *testString1 = "programming";
    const char *testString2 = "abcdef";
    const char *testString3 = "hello";
    /* Possible weaknesses found:
     *  Assignment 'testString4=NULL', assigned value is 0
     */
    const char *testString4 = NULL;

    char res1 = findFirstRepeatedChar(testString1);
    if (res1 != '\0') {
        printf("First repeated char in '%s': %c\n", testString1, res1);
    } else {
        printf("No repeated char in '%s'\n", testString1);
    }

    char res2 = findFirstRepeatedChar(testString2);
    if (res2 != '\0') {
        printf("First repeated char in '%s': %c\n", testString2, res2);
    } else {
        printf("No repeated char in '%s'\n", testString2);
    }

    char res3 = findFirstRepeatedChar(testString3);
    if (res3 != '\0') {
        printf("First repeated char in '%s': %c\n", testString3, res3);
    } else {
        printf("No repeated char in '%s'\n", testString3);
    }

    /* Possible weaknesses found:
     *  Condition 'testString4!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'testString4!=NULL' is always false
     */
    if (testString4 != NULL) {
        char res4 = findFirstRepeatedChar(testString4);
        if (res4 != '\0') {
            printf("First repeated char in '%s': %c\n", testString4, res4);
        } else {
            printf("No repeated char in '%s'\n", testString4);
        }
    } else {
        printf("No repeated char in NULL\n");
    }

    return 0;
}