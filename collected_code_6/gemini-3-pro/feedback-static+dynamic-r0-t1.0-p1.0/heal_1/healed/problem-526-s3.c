#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void capitalize_first_and_last(char *str) {
    if (str == NULL) {
        return;
    }

    int in_word = 0;
    int word_start = -1;
    int i = 0;

    while (1) {
        if (str[i] == '\0' || isspace((unsigned char)str[i])) {
            if (in_word) {
                int word_end = i - 1;
                str[word_start] = toupper((unsigned char)str[word_start]);
                str[word_end] = toupper((unsigned char)str[word_end]);
                in_word = 0;
            }
            if (str[i] == '\0') {
                break;
            }
        } else {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        }
        i++;
    }
}

int main() {
    char str[] = "hello world from c programmer";
    
    capitalize_first_and_last(str);
    
    printf("%s\n", str);
    
    return 0;
}