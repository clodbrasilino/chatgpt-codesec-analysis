#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long w);

bool is_woodall(unsigned long long w) {
    unsigned long long v;
    unsigned long long n;
    /* Possible weaknesses found:
     *  The scope of the variable 'power_of_two' can be reduced. [variableScope]
     */
    unsigned long long power_of_two;
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    unsigned long long current;

    if (w == ULLONG_MAX) {
        return false;
    }

    v = w + 1;
    n = 1;

    while (n < 64) {
        power_of_two = 1ULL << n;
        
        if (ULLONG_MAX / power_of_two < n) {
            break;
        }
        
        current = n * power_of_two;
        
        if (current == v) {
            return true;
        }
        
        if (current > v) {
            return false;
        }
        
        n++;
    }

    return false;
}

int main(void) {
    unsigned long long w;

    if (scanf("%llu", &w) != 1) {
        return 1;
    }

    if (is_woodall(w)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}