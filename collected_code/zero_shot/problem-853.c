``` 
#include <stdio.h>
int sum_of_odd_factors(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0 && i % 2 != 0) {
            sum += i;
        }
    }
    return sum;
}
