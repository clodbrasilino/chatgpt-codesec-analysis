#include <stdio.h>
#include <string.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int l, int r) {
    if (l == r)
        printf("%s\n", a);
    else {
        for (int i = l; i <= r; i++) {
            swap(a + l, a + i);
            permute(a, l + 1, r);
            swap(a + l, a + i);
        }
    }
}

int main() {
    char str[] = "aab";
    size_t n = sizeof(str) / sizeof(str[0]) - 1;
    permute(str, 0, n - 1);
    return 0;
}