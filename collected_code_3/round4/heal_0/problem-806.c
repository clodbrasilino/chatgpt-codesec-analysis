#include <stdio.h>
#include <string.h>
#include <ctype.h>

int maxRunUppercase(char* str) {
    int max_run = 0;
    int current_run = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (isupper(str[i])) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }
    return max_run;
}

int main() {
    char str[] = "Hello, WOrLD! This is A TeST String.";
    printf("Maximum run of uppercase characters: %d\n", maxRunUppercase(str));
    return 0;
}