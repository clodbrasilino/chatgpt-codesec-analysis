#include <stdio.h>
#include <string.h>

int shortestWordLength(char* str) {
    int len = strlen(str);
    int min = len, curr_len = 0;

    for (int i = 0; i <= len; i++) {
        if (str[i] != ' ' && str[i] != '\0') {
            curr_len++;
        } else {
            if (curr_len < min) {
                min = curr_len;
            }
            curr_len = 0;
        }
    }
    return min;
}

int main() {
    char str[] = "I am an experienced C developer";
    printf("Length of shortest word is: %d", shortestWordLength(str));
    return 0;
}