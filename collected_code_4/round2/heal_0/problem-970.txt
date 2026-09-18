#include <stdio.h>

int find_min(int num1, int num2) {
    return num1 < num2 ? num1 : num2;
}

int main() {
    int num1, num2, min;
    
    printf("Enter two numbers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    min = find_min(num1, num2);
    printf("Minimum is: %d\n", min);
    
    return 0;
}