#include<stdio.h>

int entringerNumber(int n, int k) {
    if (k == 0) {
        return 1;
    } else if (n == 0) {
        return 0;
    } else {
        return entringerNumber(n, k - 1) + entringerNumber(n - 1, k);
    }
}

int main(){
    int n, k;
    
    printf("Enter two integers (n k): ");
    scanf("%d%d", &n, &k);

    if (n < 0 || k < 0) {
        printf("Both integers must be positive.\n");
        return 1;
    }

    printf("Entringer number E(%d, %d) is %d\n", n, k, entringerNumber(n, k));

    return 0;
}