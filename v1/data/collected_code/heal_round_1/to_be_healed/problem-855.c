#include <stdio.h>

int checkEvenParity(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count % 2 == 0 ? 1 : 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num);
    
    if (checkEvenParity(num)) {
        printf("%d has even parity.\n", num);
    } else {
        printf("%d does not have even parity.\n", num);
    }
    
    return 0;
}