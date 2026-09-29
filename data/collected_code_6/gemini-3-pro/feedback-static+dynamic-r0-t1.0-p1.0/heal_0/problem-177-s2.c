#include <stdio.h>

void findNumbersByLCM(int L, int R) {
    if (L <= 0 || R <= 0 || L >= R) {
        printf("Invalid input range.\n");
        return;
    }

    if (L * 2 <= R) {
        printf("%d %d\n", L, L * 2);
    } else {
        printf("-1 -1\n");
    }
}

int main() {
    int L = 0, R = 0;

    if (scanf("%d %d", &L, &R) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    findNumbersByLCM(L, R);

    return 0;
}