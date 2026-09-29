#include <stdio.h>

void reverse_range(char *start, char *end) {
    if (start == NULL || end == NULL || start > end) {
        return;
    }
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str) {
    if (str == NULL) {
        return;
    }
    char *end = str;
    while (*end) {
        end++;
    }
    if (end > str) {
        reverse_range(str, end - 1);
    }
    char *word_start = str;
    char *ptr = str;
    while (*ptr) {
        if (*ptr == ' ') {
            if (ptr > word_start) {
                reverse_range(word_start, ptr - 1);
            }
            word_start = ptr + 1;
        }
        ptr++;
    }
    if (ptr > word_start) {
        reverse_range(word_start, ptr - 1);
    }
}

int main(void) {
    char str[] = "The quick brown fox jumps over the lazy dog";
    printf("%s\n", str);
    reverse_words(str);
    printf("%s\n", str);
    return 0;
}