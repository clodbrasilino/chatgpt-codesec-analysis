#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void capitalize_first_and_last(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int in_word = 0;
    int word_start = -1;

    for (int i = 0; i <= len; i++) {
        if (str[i] == '\0' || isspace((unsigned char)str[i])) {
            if (in_word) {
                int word_end = i - 1;
                str[word_start] = toupper((unsigned char)str[word_start]);
                str[word_end] = toupper((unsigned char)str[word_end]);
                in_word = 0;
            }
        } else {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        }
    }
}

int main() {
    char str[] = "hello world from c programmer";
    
    capitalize_first_and_last(str);
    
    printf("%s\n", str);
    
    return 0;
}