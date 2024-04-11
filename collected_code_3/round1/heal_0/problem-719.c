#include <stdio.h>
#include <string.h>

int match(const char *str) {
    int state = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (state == 0 && str[i] == 'a') {
            state = 1;
        } else if (state == 1 && str[i] == 'b') {
            state = 2;
        } else if (state == 2 && str[i] == 'b') {
            state = 2;
        } else {
            state = 0;
        }
        i++;
    }
    return state == 1 || state == 2;
}

int main() {
    printf("%d\n", match("a"));        // 1
    printf("%d\n", match("ab"));       // 1
    printf("%d\n", match("abb"));      // 1
    printf("%d\n", match("aabb"));     // 0
    printf("%d\n", match("ba"));       // 0
    printf("%d\n", match("b"));        // 0
    printf("%d\n", match("bb"));       // 0
    printf("%d\n", match("bbb"));      // 0
    printf("%d\n", match("aab"));      // 0
    printf("%d\n", match("abbab"));    // 0
    return 0;
}