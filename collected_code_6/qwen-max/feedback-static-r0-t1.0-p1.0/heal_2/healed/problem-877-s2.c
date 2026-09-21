#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_string(char *str, size_t len) {
    if (len <= 1) return;
    char temp;
    for (size_t i = 0; i < len-1; ++i) {
        for (size_t j = i+1; j < len; ++j) {
            if (str[i] > str[j]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    char str[] = "hello";
    printf("Original string: %s\n", str);
    size_t n = strlen(str);
    sort_string(str, n);
    printf("Sorted string: %s\n", str);
    return 0;
}