#include <stdio.h>
#include <string.h>

void reverseSubString(char* start, char* end) {
    if (!start || !end) return;
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverseWords(char* str) {
    if (!str) return;
    
    char* word_begin = str;
    char* temp = str;

    while (*temp) {
        temp++;
        if (*temp == '\0') {
            reverseSubString(word_begin, temp - 1);
        } else if (*temp == ' ') {
            reverseSubString(word_begin, temp - 1);
            word_begin = temp + 1;
        }
    }
    
    reverseSubString(str, temp - 1);
}

int main(void) {
    char str[] = "Hello World from C developer";
    
    reverseWords(str);
    
    printf("%s\n", str);
    
    return 0;
}