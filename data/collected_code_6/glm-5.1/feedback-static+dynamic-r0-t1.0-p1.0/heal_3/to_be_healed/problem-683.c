#include <stdio.h>
#include <stdlib.h>

int check_sum_of_two_squares(long long n) {
    if (n < 0) {
        return 0;
    }
    long long left = 0;
    long long right = 0;
    while (right * right <= n) {
        right++;
    }
    right--;
    while (left <= right) {
        long long sum = left * left + right * right;
        if (sum == n) {
            return 1;
        }
        if (sum < n) {
            left++;
        } else {
            right--;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long long n = atoll(argv[1]);
    if (check_sum_of_two_squares(n)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return EXIT_SUCCESS;
}