#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_abundant(int n) {
    if (n <= 0) {
        return false;
    }
    
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1867795685 + 344823816 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000019,time:32009,execs:15402,op:havoc,rep:3)
                 * UBSan: signed integer overflow: 1885330024 + 304085485 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:14844,execs:7227,op:havoc,rep:6)
                 */
                sum += n / i;
            }
        }
    }
    
    return sum > n;
}

int main(void) {
    int number;
    
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (is_abundant(number)) {
        printf("%d is an abundant number\n", number);
    } else {
        printf("%d is not an abundant number\n", number);
    }
    
    return EXIT_SUCCESS;
}