#include <stdio.h>
#include <string.h>
#include <ctype.h>

int maxLengthEvenWord(char* str) {
    int n = strlen(str);
    int res = 0, cur_len = 0;
    for (int i = 0; i < n; i++) {
        if (isalpha(str[i])) {
            cur_len++;
        } else {
            if (cur_len % 2 == 0) {
                res = (res < cur_len) ? cur_len : res;
            }
            cur_len = 0;
        }
    }
    if (cur_len % 2 == 0) {
        res = (res < cur_len) ? cur_len : res;
    }
    return res;
}

int main() {
    char str[] = "Hello, my name is John Doe and I am a software developer";
    int len = maxLengthEvenWord(str);
    printf("The maximum length of an even word is: %d\n", len);
    return 0;
}