#include <stdio.h>
#include <string.h>

int countSubstr(char str[]) {
    int result = 0;
    int n = strlen(str);
    int count[256] = {0};

    for (int i = 0; i < n; i++)
        count[str[i]]++;

    for (int i = 0; i < 256; i++)
        result += (count[i] * (count[i] + 1)) / 2;

    return result;
}

int main() {
    char str[] = "abcab";
    printf("%d", countSubstr(str));
    return 0;
}