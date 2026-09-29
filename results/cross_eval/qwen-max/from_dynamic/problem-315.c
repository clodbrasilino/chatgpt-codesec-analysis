#include <stdio.h>
#include <string.h>

int findFirstMaxLengthEvenWord(const char *words[], int n, const char **result) {
    int maxLength = 0;
    for (int i = 0; i < n; ++i) {
        size_t length = strlen(words[i]);
        if (length % 2 == 0 && length >= maxLength) {
            maxLength = length;
            *result = words[i];
        }
    }
    return maxLength;
}

int main() {
    const char *words[] = {"hello", "world", "a", "ab", "abcd", "abcdef"};
    const char *result = NULL;
    int n = sizeof(words) / sizeof(words[0]);
    int maxLength = findFirstMaxLengthEvenWord(words, n, &result);
    if (maxLength > 0) {
        printf("The first maximum length even word is: %s with length %d\n", result, maxLength);
    } else {
        printf("No even length word found.\n");
    }
    return 0;
}