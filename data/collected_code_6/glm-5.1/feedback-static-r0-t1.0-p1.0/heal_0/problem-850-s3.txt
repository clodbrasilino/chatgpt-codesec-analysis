#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    if ((unsigned int)a + (unsigned int)b + (unsigned int)c != 180) {
        return false;
    }
    return true;
}

int main() {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (is_valid_triangle(a, b, c)) {
            printf("1");
        } else {
            printf("0");
        }
    } else {
        printf("0");
    }
    return 0;
}