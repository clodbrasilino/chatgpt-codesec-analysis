#include <stdio.h>
#include <ctype.h>

int max_uppercase_run(char *str) {
    int max_run = 0, current_run = 0;
    while (*str) {
        if (isupper((unsigned char)*str)) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
        str++;
    }
    return max_run;
}

int main() {
    char str[] = "Hello, WORLDDD. How ARE You?";
    printf("Maximum run of uppercase characters: %d\n", max_uppercase_run(str));
    return 0;
}