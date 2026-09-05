#include <stdio.h>
#include <stdbool.h>

bool is_triangle_possible(int a, int b, int c) {
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
        if (is_triangle_possible(a, b, c)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    } else {
        printf("NO\n");
    }
    return 0;
}