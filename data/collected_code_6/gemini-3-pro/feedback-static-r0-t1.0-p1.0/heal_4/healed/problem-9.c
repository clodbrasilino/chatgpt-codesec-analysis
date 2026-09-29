#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 4096

int find_minimum_rotations(const char *str) {
    if (str == NULL) {
        return -1;
    }

    size_t n = 0;
    
    while (n < MAX_STR_LEN && str[n] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;
    }

    for (size_t i = 1; i <= n; i++) {
        int match = 1;
        for (size_t j = 0; j < n; j++) {
            if (str[j] != str[(i + j) % n]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return (int)i;
        }
    }

    return (int)n;
}

int main(void) {
    const char *test_str1 = "geeks";
    const char *test_str2 = "aaaa";
    const char *test_str3 = "abc";

    int res1 = find_minimum_rotations(test_str1);
    if (res1 != -1) {
        printf("%d\n", res1);
    }

    int res2 = find_minimum_rotations(test_str2);
    if (res2 != -1) {
        printf("%d\n", res2);
    }

    int res3 = find_minimum_rotations(test_str3);
    if (res3 != -1) {
        printf("%d\n", res3);
    }

    return 0;
}