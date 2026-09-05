#include <stdio.h>
#include <string.h>

int find_first_repeated(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len < 2) {
        return -1;
    }

    unsigned char char_set[256] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            return (int)c;
        }
        char_set[c] = 1;
    }

    return -1;
}

int main(void) {
    const char *test_str1 = "programming";
    const char *test_str2 = "abcdef";
    const char *test_str3 = "a";
    const char *test_str4 = NULL;

    int res1 = find_first_repeated(test_str1);
    int res2 = find_first_repeated(test_str2);
    int res3 = find_first_repeated(test_str3);
    /* Possible weaknesses found:
     *  Assignment 'res4=find_first_repeated(test_str4)', assigned value is -1
     *  Calling function 'find_first_repeated' returns -1
     */
    int res4 = find_first_repeated(test_str4);

    if (res1 != -1) {
        printf("First repeated character in '%s': %c\n", test_str1, res1);
    } else {
        printf("No repeated character found in '%s'\n", test_str1);
    }

    if (res2 != -1) {
        printf("First repeated character in '%s': %c\n", test_str2, res2);
    } else {
        printf("No repeated character found in '%s'\n", test_str2);
    }

    if (res3 != -1) {
        printf("First repeated character in '%s': %c\n", test_str3, res3);
    } else {
        printf("No repeated character found in '%s'\n", test_str3);
    }

    /* Possible weaknesses found:
     *  Condition 'res4!=-1' is always false
     *  Condition 'res4!=-1' is always false [knownConditionTrueFalse]
     */
    if (res4 != -1) {
        printf("First repeated character in 'NULL': %c\n", res4);
    } else {
        printf("No repeated character found in 'NULL'\n");
    }

    return 0;
}