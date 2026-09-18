#include <stdio.h>
#include <string.h>

int match_string(char const* str) {
    size_t len = strlen(str);
    size_t i;
    for (i = 0; i < len; ++i) {
        if (str[i] == 'a') {
            if ((i + 1) < len) {
                if (str[i + 1] == 'b') {
                    return 1;
                } else if (str[i + 1] == 'a') {
                    continue;
                } else {
                    return 0;
                }
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char str[] = "abc";
    int result = match_string(str);
    printf("Result: %d\n", result);
    return 0;
}