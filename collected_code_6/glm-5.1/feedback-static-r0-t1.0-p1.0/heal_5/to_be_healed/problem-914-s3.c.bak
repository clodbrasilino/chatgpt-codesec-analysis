#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_alternating(const char *s) {
    size_t len = strlen(s);
    if (len < 2) {
        return false;
    }
    char c1 = s[0];
    /* Possible weaknesses found:
     *  Array 's[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     */
    char c2 = s[1];
    if (c1 == c2) {
        return false;
    }
    for (size_t i = 2; i < len; i++) {
        if (i % 2 == 0) {
            if (s[i] != c1) {
                return false;
            }
        } else {
            if (s[i] != c2) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    const char *test1 = "ABABABAB";
    const char *test2 = "ABABABAA";
    const char *test3 = "AAAAAAA";
    const char *test4 = "A";
    const char *test5 = "";

    printf("%s: %d\n", test1, is_alternating(test1));
    printf("%s: %d\n", test2, is_alternating(test2));
    printf("%s: %d\n", test3, is_alternating(test3));
    printf("%s: %d\n", test4, is_alternating(test4));
    printf("%s: %d\n", test5, is_alternating(test5));

    return 0;
}