#include <stdio.h>

int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int calculateLCM(int a, int b) {
    int gcd = calculateGCD(a, b);
    return (a * b) / gcd;
}

void findNumbersWithLCMInRange(int range) {
    int found = 0;
    int a, b;

    for (a = 1; a < range; a++) {
        for (b = a + 1; b < range; b++) {
            int lcm = calculateLCM(a, b);
            if (lcm >= 1 && lcm <= range) {
                found = 1;
                printf("Two distinct numbers with LCM %d: %d, %d\n", lcm, a, b);
            }
        }
    }

    if (found == 0) {
        printf("No distinct numbers with LCM within the given range.\n");
    }
}

int main() {
    int range;
    printf("Enter the range: ");
    scanf("%d", &range);

    findNumbersWithLCMInRange(range);

    return 0;
}