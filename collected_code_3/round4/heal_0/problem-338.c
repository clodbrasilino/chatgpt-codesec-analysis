#include <stdio.h>
#include <string.h>

int countSubstr(char str[]) {
    int n = strlen(str);
    int res = 0;
    int count[256] = {0};

    for (int i = 0; i < n; i++)
        count[str[i]]++;

    for (int i = 0; i < 256; i++)
        res += (count[i] * (count[i] + 1)) / 2;

    return res;
}

int main() {
    char str[] = "abcab";
    printf("%d", countSubstr(str));
    return 0;
}