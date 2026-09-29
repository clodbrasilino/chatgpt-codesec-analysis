#include <stdio.h>
#include <stdlib.h>

int digit_distance(int a, int b) {
    int distance = 0;
    unsigned long long ua, ub;
    
    if (a < 0) ua = (unsigned long long)(-(long long)a);
    else ua = (unsigned long long)a;
    
    if (b < 0) ub = (unsigned long long)(-(long long)b);
    else ub = (unsigned long long)b;
    
    while (ua > 0 || ub > 0) {
        int digit_a = (int)(ua % 10);
        int digit_b = (int)(ub % 10);
        int diff = digit_a - digit_b;
        if (diff < 0) diff = -diff;
        distance += diff;
        ua /= 10;
        ub /= 10;
    }
    
    return distance;
}

int main(void) {
    int num1, num2;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Digit distance: %d\n", digit_distance(num1, num2));
    
    return EXIT_SUCCESS;
}