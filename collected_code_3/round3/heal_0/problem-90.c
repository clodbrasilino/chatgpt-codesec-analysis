#include <stdio.h>
#include <string.h>

int longestWordLength(char* str) {
    int n = strlen(str);
    int res = 0, curr_len = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] != ' ')
            curr_len++;
        else {
            res = (res < curr_len) ? curr_len : res;
            curr_len = 0;
        }
    }
    return (res < curr_len) ? curr_len : res;
}

int main() {
    char str[] = "I am an experienced C developer";
    printf("The length of longest word is %d\n", longestWordLength(str));
    return 0;
}