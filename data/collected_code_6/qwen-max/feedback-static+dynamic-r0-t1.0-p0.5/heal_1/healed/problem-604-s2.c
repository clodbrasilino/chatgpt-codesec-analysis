#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word_start = NULL;
    char *temp = str;
    int i;

    while (*temp) {
        if (*temp == ' ') {
            if (word_start) {
                int len = temp - word_start;
                for (i = 0; i < len / 2; i++) {
                    char t = *(word_start + i);
                    *(word_start + i) = *(word_start + len - i - 1);
                    *(word_start + len - i - 1) = t;
                }
                word_start = NULL;
            }
        } else if (word_start == NULL) {
            word_start = temp;
        }
        temp++;
    }

    if (word_start) {
        int len = temp - word_start;
        for (i = 0; i < len / 2; i++) {
            char t = *(word_start + i);
            *(word_start + i) = *(word_start + len - i - 1);
            *(word_start + len - i - 1) = t;
        }
    }
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}