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
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num);

    /* Possible weaknesses found:
     *  Cannot determine that 'part2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'part1' is initialized [premium-bughuntingUninit]
     */
    divideNumber(num, &part1, &part2);

    /* Possible weaknesses found:
     *  Cannot determine that 'part1' is initialized [premium-bughuntingUninit]
     */
    printf("Part 1: %d\n", part1);
    /* Possible weaknesses found:
     *  Cannot determine that 'part2' is initialized [premium-bughuntingUninit]
     */
    printf("Part 2: %d\n", part2);
    /* Possible weaknesses found:
     *  Cannot determine that 'part2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'part1' is initialized [premium-bughuntingUninit]
     */
    printf("Sum of digits: %d\n", sumOfDigits(part1) + sumOfDigits(part2));

    return 0;
}