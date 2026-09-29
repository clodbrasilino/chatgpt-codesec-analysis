#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t length = strlen(str);

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
    int result = countSubstrings(testString);
    printf("%d\n", result);
    return 0;
}