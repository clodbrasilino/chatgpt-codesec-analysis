#include <stdio.h>
#include <stdbool.h>

bool haveOppositeSigns(int x, int y);

bool haveOppositeSigns(int x, int y) {
    return (x < 0) != (y < 0);
}

int main(void) {
    int x;
    int y;

    if (scanf("%d %d", &x, &y) != 2) {
        return 1;
    }

    if (haveOppositeSigns(x, y)) {
        printf("Opposite signs\n");
    } else {
        printf("Same signs\n");
    }

    return 0;
}