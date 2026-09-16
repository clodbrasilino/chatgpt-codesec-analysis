#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str) {
    if (str == NULL) return;
    
    size_t len = strlen(str);
    size_t i, j = 0;
    
    for (i = 0; i < len; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str[] = "abcdefghij";
    
    printf("Original string: %s\n", str);
    remove_odd_index_chars(str);
    printf("After removing odd-index characters: %s\n", str);
    
    return 0;
}