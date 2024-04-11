#include <stdio.h>
#include <string.h>

void reverseWords(char *s) {
    char *word_begin = s;
    char *temp = s; 

    while( *temp ) {
        temp++;
        if (*temp == '\0') {
            reverse(word_begin, temp-1);
        }
        else if(*temp == ' ') {
            reverse(word_begin, temp-1);
            word_begin = temp+1;
        }
    } 

    reverse(s, temp-1);
}

void reverse(char *begin, char *end) {
    char temp;
    while (begin < end) {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

int main() {
    char s[] = "Hello World";
    char *temp = s;
    printf("Input string: %s\n", s);
    reverseWords(s);
    printf("Output string: %s\n", s);
    return 0;
}