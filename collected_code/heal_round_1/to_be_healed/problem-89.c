#include <stdio.h>

int closestSmaller(int n) {
    return n - 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int result = closestSmaller(n);
    printf("The closest smaller number than %d is %d.\n", n, result);
    
    return 0;
}