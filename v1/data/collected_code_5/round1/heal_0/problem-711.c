#include <stdio.h>
#include <stdbool.h>

bool isSameProductEvenOdd(int num) {
    int odd_product = 1, even_product = 1;
    int count = 0;
    
    while(num != 0) {
        int digit = num % 10;
        
        if(count % 2 == 0) {
            odd_product *= digit;
        } else {
            even_product *= digit;
        }
        
        num /= 10;
        count++;
    }
    
    return odd_product == even_product;
}

int main() {
    int num;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if(isSameProductEvenOdd(num)) {
        printf("The product of digits at even and odd places is same.\n");
    } else {
        printf("The product of digits at even and odd places is not same.\n");
    }
    
    return 0;
}