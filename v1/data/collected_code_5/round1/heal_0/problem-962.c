#include <stdio.h>

int sumOfEvenNumbers(int l, int r) {
    int sum = 0;
    for(int i = l; i <= r; i++) {
        if(i % 2 == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int l, r;
    printf("Please enter the lower limit 'l': ");
    scanf("%d", &l);
    printf("Please enter the upper limit 'r': ");
    scanf("%d", &r);
    if(l < 0 || r < 0 || l > r){
        printf("Invalid Input!");
        return -1;
    }
    int sum = sumOfEvenNumbers(l, r);
    printf("The sum of all even natural numbers between %d and %d is: %d\n", l, r, sum);

    return 0;
}