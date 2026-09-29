#include <stdio.h>
#include <stddef.h>

int countSubstrings(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t length = 0;

    while (length < max_len && str[length] != '\0') {
        length++;
    }

    for (size_t i = 0; i < length; i++) {
        for (size_t j = i; j < length; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *testString = "abcab";
    int result = countSubstrings(testString, 256);
    printf("%d\n", result);
    return 0;
}