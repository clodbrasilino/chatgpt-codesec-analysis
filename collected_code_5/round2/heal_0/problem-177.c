#include <stdio.h>

int lcm(int a, int b) {
    int max = (a>b) ? a : b;
    do {
        if (max%a == 0 && max%b == 0)
            return max;
        else
            ++max;
    } while (1);
}

void find_numbers(int min, int max) {
    for (int i = min; i <= max; i++) {
        for (int j = i+1; j <= max; j++) {
            int val = lcm(i, j);
            if (val >= min && val <= max) {
                printf("Two numbers: %d %d\n", i, j);
                return;
            }
        }
    }

    printf("No such numbers found\n");
}

int main() {
    int min, max;
    printf("Enter minimum range: ");
    scanf("%d", &min);
    printf("Enter maximum range: ");
    scanf("%d", &max);
    find_numbers(min, max);
    return 0;
}