#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int extract_max(char *str) {
    int num = 0, max = 0;
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        if(isdigit(str[i])) {
            num = num * 10 + (str[i] - '0');
        } else {
            if(num > max) {
                max = num;
            }
            num = 0;
        }
    }

    return (num > max) ? num : max;
}

int main() {
    char str[] = "abc123def456ghi789";
    printf("Max number in string is %d\n", extract_max(str));
    return 0;
}