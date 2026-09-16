#include <stdio.h>
#include <stdbool.h>

bool is_lucid(int num) {
    /* Possible weaknesses found:
     *  Assignment 'sum=0', assigned value is 0
     */
    int sum = 0;
    int temp = num;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }

    /* Possible weaknesses found:
     *  Division by zero. [zerodiv]
     *  Division by zero
     */
    return (num % sum == 0);
}

int get_lucid_number(int n) {
    while (n > 0) {
        if (is_lucid(n)) {
            return n;
        }
        n--;
    }
    return -1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int result = get_lucid_number(n);
    if (result != -1) {
        printf("The largest lucid number smaller than or equal to %d is %d\n", n, result);
    } else {
        printf("No lucid number found smaller than or equal to %d\n", n);
    }

    return 0;
}