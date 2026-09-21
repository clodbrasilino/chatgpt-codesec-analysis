#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    int len = 0;
    size_t i = 0;
    size_t str_len = 0;
    
    if (s == NULL) {
        return 0;
    }
    
    while (str_len < max_len && s[str_len] != '\0') {
        str_len++;
    }
    
    if (str_len == 0) {
        return 0;
    }
    
    i = str_len - 1;

    while (i > 0 && s[i] == ' ') {
        i--;
    }
    
    if (s[i] == ' ') {
        return 0;
    }

    while (i > 0 && s[i] != ' ') {
        len++;
        i--;
    }
    
    if (s[i] != ' ') {
        len++;
    }

    return len;
}

int main(void) {
    char str[1024];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, sizeof(str));
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        printf("%d\n", lengthOfLastWord(str, sizeof(str)));
    }

    return 0;
}