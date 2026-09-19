#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    unsigned long long power_of_two = 2;
    unsigned long long i = 1;

    while (1) {
        if (power_of_two - 1 > n / i) {
            break;
        }

        unsigned long long w = i * (power_of_two - 1);
        if (w == n) {
            return true;
        }
        
        if (w > n) {
            break;
        }

        i++;
        if (power_of_two > UINT64_MAX / 2) {
            break;
        }
        power_of_two <<= 1;
    }

    return false;
}

int main(void) {
    unsigned long long num;

    if (scanf("%llu", &num) != 1) {
        return 1;
    }

    if (is_woodall(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}