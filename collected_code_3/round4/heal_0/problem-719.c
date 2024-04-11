#include <stdio.h>
#include <string.h>

int match(char *str) {
    int state = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (state == 0 && str[i] == 'a') {
            state = 1;
        } else if (state == 1 && str[i] == 'b') {
            state = 2;
        } else if (state == 2 && str[i] != 'b') {
            return 0;
        }
        i++;
    }
    if (state == 0 || state == 1) {
        return 0;
    }
    return 1;
}

int main() {
    printf("%d\n", match("a"));      // 0
    printf("%d\n", match("ab"));     // 1
    printf("%d\n", match("abb"));    // 1
    printf("%d\n", match("aabb"));   // 0
    printf("%d\n", match("abc"));    // 0
    return 0;
}