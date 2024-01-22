#include<stdio.h>
#include<string.h>

void swap(char* x, char* y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char* str, int l, int r) {
    if (l == r) {
        printf("%s\n", str);
    } else {
        for (int i = l; i <= r && str[i] != '\0'; i++) {
            swap(&str[l], &str[i]);
            permute(str, l + 1, r);
            swap(&str[l], &str[i]);
        }
    }
}

int main() {
    char str[] = "AAB";
    int n = strlen(str);
    if (n < (sizeof(str) - 1)) {
        str[n] = '\0';     
        permute(str, 0, n - 1);
    }
    return 0;
}