#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

int countOddFactorNumbers(long long low, long long high, long long *result) {
    if (result == NULL) {
        return -1;
    }
    
    if (low > high) {
        return -1;
    }
    
    if (low < 0 || high < 0) {
        return -1;
    }
    
    if (high > 3037000499LL) {
        return -1;
    }
    
    if (low == 0) {
        low = 1;
    }
    
    long long sqrtHigh = (long long)sqrt((double)high);
    while ((sqrtHigh + 1) * (sqrtHigh + 1) <= high) {
        sqrtHigh++;
    }
    while (sqrtHigh * sqrtHigh > high) {
        sqrtHigh--;
    }
    
    long long sqrtLowMinusOne = 0;
    if (low > 1) {
        sqrtLowMinusOne = (long long)sqrt((double)(low - 1));
        while ((sqrtLowMinusOne + 1) * (sqrtLowMinusOne + 1) <= low - 1) {
            sqrtLowMinusOne++;
        }
        while (sqrtLowMinusOne * sqrtLowMinusOne > low - 1) {
            sqrtLowMinusOne--;
        }
    }
    
    *result = sqrtHigh - sqrtLowMinusOne;
    return 0;
}

int main(void) {
    long long low, high, result;
    
    printf("Enter the range (low high): ");
    
    if (scanf("%lld %lld", &low, &high) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (countOddFactorNumbers(low, high, &result) != 0) {
        fprintf(stderr, "Invalid range or calculation error\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of elements with odd factors: %lld\n", result);
    
    return EXIT_SUCCESS;
}