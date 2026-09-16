#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int find_numbers_in_range(int lower, int upper) {
    for (int i = lower; i <= upper; i++) {
        for (int j = i + 1; j <= upper; j++) {
            if (lcm(i, j) >= lower && lcm(i, j) <= upper) {
                printf("Found numbers: %d and %d\n", i, j);
                return 0;
            }
        }
    }
    return -1;
}

int main() {
    int lower, upper;

    printf("Enter the lower and upper bounds of the range: ");
    scanf("%d %d", &lower, &upper);

    if (find_numbers_in_range(lower, upper) == -1) {
        printf("No such numbers found in the given range.\n");
    }

    return 0;
}