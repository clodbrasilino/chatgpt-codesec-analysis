#include <stdio.h>
#include <string.h>

int flipsRequired(char *str) {
    int len = strlen(str);
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if (str[i] == str[i + 1]) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "1010101";
    printf("%d\n", flipsRequired(str));
    return 0;
}