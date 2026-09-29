#include <stdio.h>

void find_xy(int a, int b, int n, int *x, int *y) {
    int temp;
    int x0 = 1;
    int x1 = 0;
    int y0 = 0;
    int y1 = 1;
    
    while (b != 0) {
        int quotient = a / b;
        temp = b;
        b = a % b;
        a = temp;
        
        temp = x1;
        x1 = x0 - quotient * x1;
        x0 = temp;
        
        temp = y1;
        y1 = y0 - quotient * y1;
        y0 = temp;
    }
    
    *x = x0;
    *y = y0;
}

int main() {
    int a, b, n, x, y;
    printf("Enter values for a, b, and n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d %d", &a, &b, &n);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'y' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'x' is initialized [premium-bughuntingUninit]
     */
    find_xy(a, b, n, &x, &y);
    /* Possible weaknesses found:
     *  Cannot determine that 'y' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'x' is initialized [premium-bughuntingUninit]
     */
    printf("x = %d, y = %d\n", x, y);
    
    return 0;
}