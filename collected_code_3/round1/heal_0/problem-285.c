#include <stdio.h>
#include <string.h>

int match(const char *str) {
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(str[i] == 'a' && i+2 < length && str[i+1] == 'b' && str[i+2] == 'b') {
            return 1;
        }
        if(str[i] == 'a' && i+3 < length && str[i+1] == 'b' && str[i+2] == 'b' && str[i+3] == 'b') {
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("%d\n", match("abc"));       // 0
    printf("%d\n", match("abb"));       // 1
    printf("%d\n", match("abbb"));      // 1
    printf("%d\n", match("abbbb"));     // 0
    return 0;
}