#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    if (s == NULL) {
        return 0;
    }
    
    size_t len = strnlen(s, max_len);
    int i = (int)len - 1;
    
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int result = lengthOfLastWord(argv[1], 1024);
    printf("%d\n", result);
    
    return 0;
}