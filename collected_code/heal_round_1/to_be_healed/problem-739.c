#include <stdio.h>

int smallestTriangularNumberIndex(int n) {
    int index = 1;
    int triangularNum = 1;
    
    while (triangularNum <= n) {
        index++;
        triangularNum = (index * (index + 1)) / 2;
    }
    
    return index;
}

int main() {
    int n;
    printf("Enter the number of digits: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int index = smallestTriangularNumberIndex(n);
    printf("Index of smallest triangular number with %d digits is %d\n", n, index);
    
    return 0;
}