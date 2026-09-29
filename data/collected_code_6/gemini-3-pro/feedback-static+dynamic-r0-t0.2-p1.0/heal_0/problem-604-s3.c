#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *start, char *end) {
    if (start == NULL || end == NULL) {
        return;
    }
    char temp;
    while (start < end) {
        temp = *start;
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

    char *word_start = str;
    char *temp = str;

    while (*temp) {
        temp++;
        if (*temp == '\0') {
            reverse_string(word_start, temp - 1);
        } else if (*temp == ' ') {
            reverse_string(word_start, temp - 1);
            word_start = temp + 1;
        }
    }

    reverse_string(str, temp - 1);
}

int main(void) {
    char str[] = "Hello World from C";
    
    reverse_words(str);
    
    printf("%s\n", str);
    
    return 0;
}