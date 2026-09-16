#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_keith_number(int n) {
    if (n < 10) return false;
    
    int temp = n;
    int digits = 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    int *seq = (int *)malloc(digits * sizeof(int));
    if (seq == NULL) return false;
    
    temp = n;
    for (int i = digits - 1; i >= 0; i--) {
        seq[i] = temp % 10;
        temp /= 10;
    }
    
    int sum = 0;
    while (sum < n) {
        sum = 0;
        for (int i = 0; i < digits; i++) {
            sum += seq[i];
        }
        
        if (sum == n) {
            free(seq);
            return true;
        }
        
        for (int i = 0; i < digits - 1; i++) {
            seq[i] = seq[i + 1];
        }
        seq[digits - 1] = sum;
    }
    
    free(seq);
    return false;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_keith_number(num)) {
        printf("%d is a Keith number\n", num);
    } else {
        printf("%d is not a Keith number\n", num);
    }
    
    return 0;
}