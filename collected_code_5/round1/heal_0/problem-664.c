#include <stdio.h>

double average_of_evens(int n)
{
    int sum = 0, count = 0;
    for(int i = 0; i <= n; i++){
        if(i % 2 == 0){
            sum += i;
            count++;
        }
    }
    if(count == 0) return 0;
    return (double)sum/count;
}

int main(){
    int number;
    printf("Enter an even number till which you want to find the average: ");
    scanf("%d", &number);
    if(number % 2 != 0){
        printf("The number entered is not even.\n");
        return 1;
    }
    printf("Average of even numbers till %d is %.2f\n", number, average_of_evens(number));
    return 0;
}