#include <stdio.h>
#include <string.h>

void remove_even_chars(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; ) {
        if ((i % 2) == 0 && i != 0) {
            for (int j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
        } else {
            i++;
        }
    }
}

int main() {
    char str[] = "abcdefghijklmnopqrstuvwxyz";
    printf("Original String: %s\n", str);
    remove_even_chars(str);
    printf("Modified String: %s\n", str);
    return 0;
}