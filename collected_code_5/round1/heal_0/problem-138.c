#include <stdio.h>
#include <stdbool.h>

bool checkPowersOfTwo(int n) {
    if(n <= 0)
        return false;
    return ((n & (n - 1)) == 0);
}

int main() {
    int number = 0;
    printf("Enter a number: \n");
    scanf("%d", &number);

    if(checkPowersOfTwo(number)) {
        printf("Number can be represented as sum of non-zero powers of 2.\n");
    } else {
        printf("Number can NOT be represented as sum of non-zero powers of 2.\n");
    }

    return 0;
}