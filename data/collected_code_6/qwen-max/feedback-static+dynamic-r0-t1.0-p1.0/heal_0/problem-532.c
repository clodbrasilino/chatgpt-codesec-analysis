#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int are_permutations(const char *str1, const char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return 0;
    }
    int len = strlen(str1);
    int count[256] = {0};
    for (int i = 0; i < len; ++i) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    const char *str1 = "abc";
    const char *str2 = "cba";
    if (are_permutations(str1, str2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}