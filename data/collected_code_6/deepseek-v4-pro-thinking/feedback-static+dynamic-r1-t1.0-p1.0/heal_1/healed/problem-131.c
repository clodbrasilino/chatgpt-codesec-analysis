#include <stdio.h>
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

void reverseVowels(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }

    size_t len = 0;
    while (len < size && str[len] != '\0') {
        len++;
    }

    size_t left = 0;
    size_t right = len;

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

int main(void) {
    char str[] = "leetcode";
    reverseVowels(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}