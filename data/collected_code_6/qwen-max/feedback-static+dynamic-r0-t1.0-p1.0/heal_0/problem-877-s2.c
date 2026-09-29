#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_string(char *str) {
    int n = strlen(str);
    char temp;
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
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
    sort_string(str);
    printf("Sorted string: %s\n", str);
    return 0;
}