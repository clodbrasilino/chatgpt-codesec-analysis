#include <stdio.h>

int countUnsetBits(int n) {
    int count = 0;
    while (n) {
        count += 32 - __builtin_popcount(n);
        n--;
    }
    return count;
}

int main() {
    int n = 0;
    printf("Enter a number: ");
    if(scanf("%d", &n)!=1){
        printf("Failed to read integer.\n");
        return 1;
    }
    printf("Total number of unset bits: %d\n", countUnsetBits(n));
    return 0;
}
