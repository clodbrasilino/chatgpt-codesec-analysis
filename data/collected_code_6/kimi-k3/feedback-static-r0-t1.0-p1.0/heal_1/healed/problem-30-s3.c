#include <stdio.h>
#include <string.h>
#include <stddef.h>

int countSubstrings(const char *str, size_t max_len) {
    if (str == NULL) {
        return -1;
    }

    size_t n = 0;
    while (n < max_len && str[n] != '\0') {
        n++;
    }

    if (n == max_len && str[n] != '\0') {
        return -1;
    }

    int count = 0;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i; j < n; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *str = "abcab";
    int result = countSubstrings(str, 1024);

    if (result >= 0) {
        printf("Count of substrings starting and ending with same characters: %d\n", result);
    } else {
        printf("Invalid input string.\n");
    }

    return 0;
}