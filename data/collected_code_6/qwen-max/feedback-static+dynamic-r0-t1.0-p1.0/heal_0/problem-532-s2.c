#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool are_permutations(const char *str1, const char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    int count[256] = {0};
    for (int i = 0; str1[i]; ++i) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *str1 = "listen";
    const char *str2 = "silent";
    if (are_permutations(str1, str2)) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }
    return 0;
}