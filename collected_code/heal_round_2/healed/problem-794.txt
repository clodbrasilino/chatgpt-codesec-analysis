#include <stdio.h>
#include <string.h>

int matchString(const char* str) {
    int i = 0;
    int len = strnlen(str, 102);
    while (i < len-2) {
        if (str[i] == 'a' && str[i + 2] == 'b') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    char str[102] = {0};
    printf("Enter a string: ");
    scanf("%101s", str);
    int result = matchString(str);
    if (result == 1) {
        printf("String matches the pattern.\n");
    } else {
        printf("String does not match the pattern.\n");
    }
    return 0;
}