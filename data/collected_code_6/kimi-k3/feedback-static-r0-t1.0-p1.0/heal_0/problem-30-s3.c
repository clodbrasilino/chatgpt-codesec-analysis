#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int n = strlen(str);
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *str = "abcab";
    int result = countSubstrings(str);

    if (result >= 0) {
        printf("Count of substrings starting and ending with same characters: %d\n", result);
    } else {
        printf("Invalid input string.\n");
    }

    return 0;
}