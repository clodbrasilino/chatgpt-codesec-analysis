#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int canRearrange(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int counts[256] = {0};
    int maxCount = 0;
    int len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > maxCount) {
            maxCount = counts[c];
        }
        len++;
    }

    if (maxCount > (len + 1) / 2) {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test1 = "aab";
    const char *test2 = "aaab";
    const char *test3 = "abc";

    printf("%d\n", canRearrange(test1));
    printf("%d\n", canRearrange(test2));
    printf("%d\n", canRearrange(test3));
    printf("%d\n", canRearrange(NULL));

    return 0;
}