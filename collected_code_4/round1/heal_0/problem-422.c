#include <stdio.h>

double find_average_cubes(int n){
    double sum = 0;
    for(int i = 0; i <= n; i++){
        sum += i*i*i;
    }
    return sum/n;
}

int main(){
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    if(n <= 0){
        printf("Input must be a positive integer.\n");
        return -1;
    }

    double result = find_average_cubes(n);
    printf("The average of cubes of first %d natural numbers is %.2lf", n, result);
   
    return 0;
}