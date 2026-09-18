#include <stdio.h>

int check_abundant(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n)
                sum = sum + i + n / i;
            else
                sum = sum + i;
        }
    }
    if (sum > n && n != 0)
        return 1;   // It means number is abundant
     
    return 0;   // It means number is not abundant
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d",&number);
    
    if(check_abundant(number))
       printf("The number is abundant.\n");
    else
       printf("The number is not abundant.\n");
   
    return 0;
}