#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char *begin, char *end) {
    char temp;
    if (begin == NULL || end == NULL) {
        return;
    }
    while (begin < end) {
        temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }
}

void reverseWords(char *str) {
    char *word_begin = str;
    char *temp = str;

    if (str == NULL) {
        return;
    }

    while (*temp) {
        temp++;
        if (*temp == '\0') {
            reverseString(word_begin, temp - 1);
        } else if (*temp == ' ') {
            reverseString(word_begin, temp - 1);
            word_begin = temp + 1;
        }
    }
    reverseString(str, temp - 1);
}

int main() {
    char str[] = "Hello World from C developer";
    
    reverseWords(str);
    
    printf("%s\n", str);
    
    return 0;
}