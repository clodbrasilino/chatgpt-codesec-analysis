#include <stdio.h>

int add_two_integers(int a, int b, int lower, int upper) {
    int sum = a + b;
    if (sum >= lower && sum <= upper) {
        return 20;
    }
    return sum;
}

int main(void) {
    int result = add_two_integers(5, 7, 10, 15);
    printf("%d\n", result);
    return 0;
}