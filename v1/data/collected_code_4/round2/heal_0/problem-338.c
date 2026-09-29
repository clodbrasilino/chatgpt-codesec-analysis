#include <stdio.h>
#include <string.h>

int countSubstringWithEqualEnds(char* s) {
    int n = strlen(s);
    int result = 0;
    int count[256] = {0};

    for (int i = 0; i < n; i++)
        count[s[i]]++;

    for (int i = 0; i < 256; i++)
        result = result + ((count[i] * (count[i] + 1)) / 2);

    return result;
}

int main() {
    char s[] = "abcab";
    printf("%d", countSubstringWithEqualEnds(s));
    return 0;
}