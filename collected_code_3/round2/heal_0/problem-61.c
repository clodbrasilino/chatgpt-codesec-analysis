#include <stdio.h>
#include <string.h>

int countSubstrings(char* str) {
    int count = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int sum = 0;
        for (int j = i; j < len; j++) {
            sum += str[j] - '0';
            if (sum == (j - i + 1)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    char str[] = "1234";
    printf("%d\n", countSubstrings(str));
    return 0;
}