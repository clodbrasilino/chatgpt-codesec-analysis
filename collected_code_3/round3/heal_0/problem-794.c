#include <stdio.h>
#include <string.h>

int match(char str[]) {
    int len = strlen(str);
    int i, a_index = -1;

    for(i = 0; i < len; i++) {
        if(str[i] == 'a') {
            a_index = i;
        }
        if(str[i] == 'b' && a_index != -1) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char str1[] = "abc";
    char str2[] = "bca";
    printf("%d\n", match(str1)); // 1
    printf("%d\n", match(str2)); // 0
    return 0;
}