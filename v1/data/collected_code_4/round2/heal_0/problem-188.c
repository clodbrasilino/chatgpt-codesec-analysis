#include <stdio.h>
#include <math.h>

int isProductOfSquares(int n) {
    int i, j;
    for(i=0; i<=sqrt(n); i++) {
        for(j=i; j<=sqrt(n); j++) {
            if(i*i*j*j == n) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(isProductOfSquares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}