#include <stdio.h>

// Function to find nth number in a sequence that is not a multiple of m
int nthNonMultiple(int n, int m) {
    int count = 0, i = 1;
    
    while(1) {
        if(i % m != 0) {
            count++;
            if(count == n)
                return i;
        }
        i++;
    }
}

int main() {
    int n, m;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter m: ");
    scanf("%d", &m);

    if(n < 0 || m <= 0) {
        printf("Invalid values entered for n or m!");
        return -1;
    }

    int res = nthNonMultiple(n, m);

    printf("%dth number in the sequence that is not a multiple of %d is %d.\n", n, m, res);

    return 0;
}