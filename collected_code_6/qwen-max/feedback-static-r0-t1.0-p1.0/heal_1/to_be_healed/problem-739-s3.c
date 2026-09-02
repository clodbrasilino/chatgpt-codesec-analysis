#include <stdio.h>
#include <math.h>

long long triangular_index(int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'num_digits' can be reduced. [variableScope]
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    long long low = 1, high = 1000000, mid, num_digits;
    while (low < high) {
        mid = (low + high) / 2;
        long long triangular_num = mid * (mid + 1) / 2;
        num_digits = (long long)(log10(triangular_num) + 1);
        if (num_digits < n)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", triangular_index(n));
    return 0;
}