#include <stdio.h>
#include <string.h>
#include <stddef.h>

static int isVowel(char c) {
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}

void reverseVowels(char *str, size_t length) {
    if (str == NULL) {
        return;
    }

    size_t left = 0;
    size_t right = length;

    while (left < right) {
        if (!isVowel(str[left])) {
            left++;
        } else if (!isVowel(str[right - 1])) {
            right--;
        } else {
            char temp = str[left];
            str[left] = str[right - 1];
            str[right - 1] = temp;
            left++;
            right--;
        }
    }
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        i++;
    }
    return i;
}

int main(void) {
    char str[] = "leetcode";
    size_t len = safe_strlen(str, sizeof(str));

    reverseVowels(str, len);
    printf("%s\n", str);

    return 0;
}