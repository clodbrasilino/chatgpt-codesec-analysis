#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    size_t i = strlen(s);
    
    while (i > 0 && s[i - 1] == ' ') {
        i--;
    }
    
    if (i == 0) {
        return 0;
    }
    
    int count = 0;
    while (i > 0 && s[i - 1] != ' ') {
        count++;
        i--;
    }
    
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int result = lengthOfLastWord(argv[1]);
    printf("%d\n", result);
    
    return 0;
}