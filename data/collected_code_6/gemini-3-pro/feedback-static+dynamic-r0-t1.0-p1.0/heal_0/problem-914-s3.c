#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkAlternating(const char *str) {
    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return 0;
    }

    char first = str[0];
    char second = str[1];

    if (first == second) {
        return 0;
    }

    for (size_t i = 2; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (str[i] != first) {
                return 0;
            }
        } else {
            if (str[i] != second) {
                return 0;
            }
        }
    }

    return 1;
}

int main(void) {
    const char *test1 = "ababab";
    const char *test2 = "ab";
    const char *test3 = "a";
    const char *test4 = "abcaba";
    const char *test5 = "aaaaa";
    const char *test6 = NULL;

    printf("%d\n", checkAlternating(test1));
    printf("%d\n", checkAlternating(test2));
    printf("%d\n", checkAlternating(test3));
    printf("%d\n", checkAlternating(test4));
    printf("%d\n", checkAlternating(test5));
    printf("%d\n", checkAlternating(test6));

    return 0;
}