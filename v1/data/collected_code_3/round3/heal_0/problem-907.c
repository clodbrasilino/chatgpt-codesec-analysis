#include <stdio.h>
#include <stdlib.h>

void findLuckyNumbers(int n) {
    int luckyNumbers[n];
    int i, j;

    for(i=0; i<n; i++) {
        luckyNumbers[i] = i*2 + 1;
    }

    for(i=1; i<n; i++) {
        if(luckyNumbers[i] != -1) {
            for(j=luckyNumbers[i]-1; j<n; j+=luckyNumbers[i]) {
                luckyNumbers[j] = -1;
            }
        }
    }

    for(i=0; i<n; i++) {
        if(luckyNumbers[i] != -1) {
            printf("%d ", luckyNumbers[i]);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of lucky numbers to print: ");
    scanf("%d", &n);
    findLuckyNumbers(n);
    return 0;
}