#include <stdio.h>
#include <stdlib.h>

double average_of_odds(int n) {
    if (n < 1 || n % 2 == 0) {
        return 0.0;
    }
    
    long long sum = 0;
    int count = 0;
    
    for (int i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }
    
    return (double)sum / count;
}

int main(void) {
    int input;
    
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }
    
    if (input < 1 || input % 2 == 0) {
        return EXIT_FAILURE;
    }
    
    double result = average_of_odds(input);
    printf("%f\n", result);
    
    return EXIT_SUCCESS;
}