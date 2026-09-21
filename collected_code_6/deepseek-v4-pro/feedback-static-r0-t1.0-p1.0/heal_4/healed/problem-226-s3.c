#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) return;
    
    size_t i, j = 0;
    size_t str_len = strnlen(str, max_len);
    
    for (i = 0; i < str_len; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    if (j < max_len) {
        str[j] = '\0';
    } else {
        str[max_len - 1] = '\0';
    }
}

int main(void) {
    char str[32] = "abcdefghij";
    
    printf("Original string: %s\n", str);
    remove_odd_index_chars(str, sizeof(str));
    printf("After removing odd-index characters: %s\n", str);
    
    return 0;
}