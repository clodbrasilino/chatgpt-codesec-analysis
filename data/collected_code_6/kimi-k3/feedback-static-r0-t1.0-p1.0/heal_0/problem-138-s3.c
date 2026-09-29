#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isSumOfNonZeroPowersOf2(unsigned int num) {
    return (num > 0) && ((num & (num - 1)) == 0);
}

int main(void) {
    unsigned int num;
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (isSumOfNonZeroPowersOf2(num)) {
        printf("%u can be represented as sum of non-zero powers of 2\n", num);
    } else {
        printf("%u cannot be represented as sum of non-zero powers of 2\n", num);
    }
    return 0;
}