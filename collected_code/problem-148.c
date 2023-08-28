#include <stdio.h>

int sumOfDigits(int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

void divideNumber(int num, int *part1, int *part2) {
    *part1 = num / 2;
    *part2 = num - *part1;
}

int main() {
    int num, part1, part2;
    printf("Enter a number: ");
    scanf("%d", &num);

    divideNumber(num, &part1, &part2);

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);
    printf("Sum of digits: %d\n", sumOfDigits(part1) + sumOfDigits(part2));

    return 0;
}