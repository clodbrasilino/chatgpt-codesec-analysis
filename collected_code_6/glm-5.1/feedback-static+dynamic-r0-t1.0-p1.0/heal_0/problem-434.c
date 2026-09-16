#include <stdio.h>
#include <stdbool.h>

bool match_a_followed_by_b(const char *str) {
    if (str == NULL) {
        return false;
    }

    const char *p = str;

    while (*p != '\0') {
        if (*p == 'a') {
            p++;
            if (*p != 'b') {
                continue;
            }
            int count = 0;
            while (*p == 'b') {
                count++;
                p++;
            }
            if (count >= 1) {
                return true;
            }
        } else {
            p++;
        }
    }
    return false;
}

int main(void) {
    const char *test1 = "ac";
    const char *test2 = "abb";
    const char *test3 = "ab";
    const char *test4 = "a";
    const char *test5 = "cab";
    const char *test6 = NULL;

    printf("%d\n", match_a_followed_by_b(test1));
    printf("%d\n", match_a_followed_by_b(test2));
    printf("%d\n", match_a_followed_by_b(test3));
    printf("%d\n", match_a_followed_by_b(test4));
    printf("%d\n", match_a_followed_by_b(test5));
    printf("%d\n", match_a_followed_by_b(test6));

    return 0;
}