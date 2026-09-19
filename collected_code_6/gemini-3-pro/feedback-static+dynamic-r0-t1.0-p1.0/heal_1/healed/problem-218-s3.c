#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min_operations(int num1, int num2) {
    long long diff = llabs((long long)num1 - (long long)num2);
    long long steps = 0;
    long long current_sum = 0;

    while (current_sum < diff || (current_sum - diff) % 2 != 0) {
        steps++;
        current_sum += steps;
    }

    return (int)steps;
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    int result = min_operations(num1, num2);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}