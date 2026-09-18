#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define N 5

void reverseString(char* str) {
    int len = strlen(str);

    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main() {
    char str_list[N][MAX_LEN] = {
        "hello",
        "world",
        "foo",
        "bar",
        "bazinga",
    };

    for (int i = 0; i < N; i++) {
        reverseString(str_list[i]);
    }

    for (int i = 0; i < N; i++) {
        puts(str_list[i]);
    }

    return 0;
}