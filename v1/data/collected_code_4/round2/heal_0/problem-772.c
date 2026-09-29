#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void remove_words_of_length_k(char* str, int k) {
    char *start, *end, *last;
    int length;

    last = str;

    while(*last) {
        while(*last == ' ') {
            ++last;
        }

        start = last;
        while(*last && (*last != ' ')) {
            ++last;
        }

        end = last;

        length = end - start;
        
        if(length == k) {
            while(*end) {
                *start = *end;
                ++start;
                ++end;
            }
            *start = '\0';
        }

        last = end;
    }
}

int main() {
    char example[256] = "This is a test sentence";
    int k = 2;

    printf("Original string: %s\n", example);
    remove_words_of_length_k(example, k);
    printf("Modified string: %s\n", example);

    return 0;
}