#include <stdio.h>

int all_unique(const char *str) {
    unsigned char seen[32] = {0};
    const unsigned char *p;

    if (str == NULL) {
        return 0;
    }

    p = (const unsigned char *)str;

    while (*p != '\0') {
        unsigned char c = *p;
        int index = c / 8;
        int bit = c % 8;
        unsigned char mask = (unsigned char)(1u << bit);

        if ((seen[index] & mask) != 0) {
            return 0;
        }

        seen[index] |= mask;
        p++;
    }

    return 1;
}

int main(void) {
    const char *test1 = "abc";
    const char *test2 = "aba";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("%d\n", all_unique(test1));
    printf("%d\n", all_unique(test2));
    printf("%d\n", all_unique(test3));
    printf("%d\n", all_unique(test4));

    return 0;
}