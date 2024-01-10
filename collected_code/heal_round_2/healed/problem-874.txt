#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkConcatenation(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL || str1[0] == '\0' || str2[0] == '\0') {
        return false;
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 % len2 != 0) {
        return false;
    }

    for (int i = 0; i < len1; i += len2) {
        if (strncmp(str1 + i, str2, len2) != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    char str1[] = "abcabcabc";
    char str2[] = "abc";

    if (checkConcatenation(str1, str2)) {
        printf("String is a concatenation of another string\n");
    } else {
        printf("String is not a concatenation of another string\n");
    }

    return 0;
}