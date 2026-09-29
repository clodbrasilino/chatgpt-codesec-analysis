#include <stdio.h>
#include <string.h>

int flipsRequired(char *str) {
    int len = strlen(str);
    int flipCount = 0;
    int i;

    for(i = 1; i < len; i++) {
        if(str[i] == str[i-1]) {
            flipCount++;
        }
    }

    return flipCount;
}

int main() {
    char str[] = "1010101";
    printf("%d\n", flipsRequired(str));
    return 0;
}