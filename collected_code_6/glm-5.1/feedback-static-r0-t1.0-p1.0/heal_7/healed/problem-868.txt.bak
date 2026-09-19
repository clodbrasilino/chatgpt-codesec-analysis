#include <stdio.h>
#include <string.h>
#include <stddef.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    size_t len = strlen(s);
    int i = (len == 0) ? -1 : (int)(len - 1);
    
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    
    if (i < 0) {
        return 0;
    }
    
    int count = 0;
    while (i >= 0 && s[i] != ' ') {
        count++;
        i--;
    }
    
    return count;
}

int main(int argc, char * const * argv) {
    if (argc < 2) {
        return 1;
    }
    
    int result = lengthOfLastWord(argv[1]);
    printf("%d\n", result);
    
    return 0;
}