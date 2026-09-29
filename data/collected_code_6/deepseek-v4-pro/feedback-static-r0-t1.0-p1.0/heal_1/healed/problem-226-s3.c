#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) return;
    
    size_t i, j = 0;
    
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str[32] = "abcdefghij";
    
    printf("Original string: %s\n", str);
    remove_odd_index_chars(str, sizeof(str));
    printf("After removing odd-index characters: %s\n", str);
    
    return 0;
}