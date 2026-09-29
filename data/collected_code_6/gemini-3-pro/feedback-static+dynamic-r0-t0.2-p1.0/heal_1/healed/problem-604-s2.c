#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *start, char *end) {
    if (!start || !end) return;
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

void reverse_words(char *str) {
    char *word_start = str;
    char *temp = str;

    if (!str) return;

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