#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    if (s == NULL || max_len == 0) {
        return 0;
    }
    
    size_t len = strnlen(s, max_len);
    
    if (len == 0) {
        return 0;
    }
    
    size_t i = len - 1;
    
    while (i > 0 && s[i] == ' ') {
        i--;
    }
    
    if (s[i] == ' ') {
        return 0;
    }
    
    int count = 0;
    while (i > 0 && s[i] != ' ') {
        count++;
        i--;
    }
    
    if (i == 0 && s[0] != ' ') {
        count++;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    size_t max_len = 1024;
    size_t len = strnlen(argv[1], max_len);
    if (len >= max_len) {
        return 1;
    }
    
    int result = lengthOfLastWord(argv[1], max_len);
    printf("%d\n", result);
    
    return 0;
}