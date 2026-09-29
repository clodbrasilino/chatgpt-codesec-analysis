#include <stdio.h>

int isLucky(int n) {
    int counter = 2;
    
    while (n >= counter) {
        if (n % counter == 0) {
            return 0;
        }
        
        n -= n / counter;
        counter++;
    }
    
    return 1;
}

void printLuckyNumbers(int n) {
    int i, count = 0;
    
    for (i = 1; count < n; i++) {
        if (isLucky(i)) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\n");
}

int main() {
    int n = 0;
    
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    if (n > 0) {
        printf("First %d lucky numbers are: ", n);
        printLuckyNumbers(n);
    } else {
        printf("Please enter a positive number.\n");
    }
    
    return 0;
}