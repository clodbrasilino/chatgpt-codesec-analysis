#include <stdio.h>
#include <string.h>

void reverse(char *begin, char *end) {
    char temp;
    while (begin < end) {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

void reverseWords(char *s) {
    char *word_begin = s;
    char *temp = s; 

    while (*temp) {
        temp++;
        if (*temp == '\0') {
            reverse(word_begin, temp - 1);
        } else if (*temp == ' ') {
            reverse(word_begin, temp - 1);
            word_begin = temp + 1;
        }
    } 

    reverse(s, temp - 1);
}

int main() {
    char s[] = "I am a C developer";
    printf("Original string: %s \n", s);
    reverseWords(s);
    printf("Reversed string: %s \n", s);
    return 0;
}