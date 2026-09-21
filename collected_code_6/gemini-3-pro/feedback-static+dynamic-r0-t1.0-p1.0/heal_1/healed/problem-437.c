#include <stdio.h>
#include <stdlib.h>

void remove_odd_characters(char *str) {
    if (str == NULL) {
        return;
    }

    size_t j = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str[] = "abcdefgh";
    
    printf("Original string: %s\n", str);
    
    remove_odd_characters(str);
    
    printf("Modified string: %s\n", str);
    
    return 0;
}