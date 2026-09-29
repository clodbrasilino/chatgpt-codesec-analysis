#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        for (size_t j = i; str[j] != '\0'; j++) {
            if (str[i] == str[j]) {
                if (count < INT_MAX) {
                    count++;
                } else {
                    return count;
                }
            }
        }
    }

    return count;
}

int main(void) {
    const char *test_str = "aba";
    int result = count_substrings(test_str);
    printf("%d\n", result);

    const char *test_str2 = "abcab";
    result = count_substrings(test_str2);
    printf("%d\n", result);

    return 0;
}