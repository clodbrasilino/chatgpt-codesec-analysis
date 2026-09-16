#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return false;
    }

    int counts[256] = {0};

    for (size_t i = 0; i < len1; i++) {
        counts[(unsigned char)str1[i]]++;
    }

    for (size_t i = 0; i < len2; i++) {
        counts[(unsigned char)str2[i]]--;
        if (counts[(unsigned char)str2[i]] < 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *str1 = "listen";
    const char *str2 = "silent";
    const char *str3 = "hello";
    const char *str4 = "world";

    if (are_permutations(str1, str2)) {
        printf("\"%s\" and \"%s\" are permutations.\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not permutations.\n", str1, str2);
    }

    if (are_permutations(str3, str4)) {
        printf("\"%s\" and \"%s\" are permutations.\n", str3, str4);
    } else {
        printf("\"%s\" and \"%s\" are not permutations.\n", str3, str4);
    }

    return 0;
}