#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isLowercase(const char c) {
    return (c >= 'a' && c <= 'z');
}

void removeLowercaseSubstrings(char* str, size_t len) {
    if(str == NULL) {
        return;
    }
    
    size_t i = 0;
      
    while(i < len) {
        if(isLowercase(str[i])) {
            size_t j = i + 1;
            while(j < len && isLowercase(str[j])) {
                j++;
            }
            memmove(&str[i], &str[j], len - j + 1);
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            len = strlen(str);
        } else {
            i++;
        }
    }
}

int main() {
    char str[] = "HeLLo WOrLd";
    size_t str_len = sizeof(str) / sizeof(char) - 1;
    removeLowercaseSubstrings(str, str_len);
    printf("%s\n", str);

    return 0;
}