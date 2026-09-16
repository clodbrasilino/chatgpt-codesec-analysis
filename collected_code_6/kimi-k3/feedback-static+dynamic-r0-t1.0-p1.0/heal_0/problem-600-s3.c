#include <stdio.h>
#include <limits.h>

int is_even(int num) {
    return !(num & 1);
}

int main(void) {
    int num;
    char term;
    
    printf("Enter an integer: ");
    
    if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_even(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
    
    return 0;
}