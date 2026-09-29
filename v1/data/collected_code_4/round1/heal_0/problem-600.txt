#include <stdio.h>

int isEven(int num) {
    return !(num & 1);
}
 
int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
 
    if (isEven(num)) {
        printf("%d is an even number.\n", num);
    } else {
        printf("%d is an odd number.\n", num);
    }
 
    return 0;
}