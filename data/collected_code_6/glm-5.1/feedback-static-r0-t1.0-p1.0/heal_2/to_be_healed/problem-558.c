#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int digit_distance(int a, int b) {
    long long val_a = a;
    long long val_b = b;
    if (val_a < 0) val_a = -val_a;
    if (val_b < 0) val_b = -val_b;
    
    int dist = 0;
    while (val_a > 0 || val_b > 0) {
        dist += abs((int)(val_a % 10 - val_b % 10));
        val_a /= 10;
        val_b /= 10;
    }
    return dist;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return 1;
    }
    
    long long input1 = strtoll(argv[1], NULL, 10);
    long long input2 = strtoll(argv[2], NULL, 10);
    
    if (input1 > INT_MAX || input1 < INT_MIN || input2 > INT_MAX || input2 < INT_MIN) {
        fprintf(stderr, "Input out of integer range\n");
        return 1;
    }
    
    int a = (int)input1;
    int b = (int)input2;
    
    printf("%d\n", digit_distance(a, b));
    return 0;
}