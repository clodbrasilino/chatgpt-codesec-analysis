#include <stdio.h>

int countUnsetBits(int n) {
    int count = 0;
    for (int num = 1; num <= n; num++) {
        /* Possible weaknesses found:
         *  Assuming that condition 'bit<sizeof(int)*8' is not redundant
         */
        for (int bit = 0; bit < sizeof(int) * 8; bit++) {
            /* Possible weaknesses found:
             *  Integer overflow
             *  Signed integer overflow for expression '1<<bit'. [integerOverflow]
             */
            if ((num & (1 << bit)) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    printf("Total unset bits from 1 to %d: %d\n", n, countUnsetBits(n));
    return 0;
}