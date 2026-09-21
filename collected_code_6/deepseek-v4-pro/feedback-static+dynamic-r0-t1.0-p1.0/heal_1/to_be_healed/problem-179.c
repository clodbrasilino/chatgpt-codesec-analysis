#include <stdio.h>
#include <stdlib.h>

int is_keith_number(int n) {
    if (n < 10) return 0;
    
    int temp = n;
    int digits = 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    int *sequence = (int*)malloc(digits * sizeof(int));
    if (sequence == NULL) {
        return 0;
    }
    
    temp = n;
    for (int i = digits - 1; i >= 0; i--) {
        sequence[i] = temp % 10;
        temp /= 10;
    }
    
    int sum = 0;
    while (sum < n) {
        sum = 0;
        for (int i = 0; i < digits; i++) {
            sum += sequence[i];
        }
        
        if (sum == n) {
            free(sequence);
            return 1;
        }
        
        for (int i = 0; i < digits - 1; i++) {
            sequence[i] = sequence[i + 1];
        }
        sequence[digits - 1] = sum;
    }
    
    free(sequence);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int num = atoi(argv[1]);
    
    if (is_keith_number(num)) {
        printf("%d is a Keith number\n", num);
    } else {
        printf("%d is not a Keith number\n", num);
    }
    
    return 0;
}