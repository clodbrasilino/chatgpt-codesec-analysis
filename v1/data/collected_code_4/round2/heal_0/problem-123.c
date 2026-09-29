#include <stdio.h>

int sum_of_div(int num){
    int sum = 1;
    for (int i = 2; i * i <= num; i++){
        if (num % i == 0){
            sum += i;
            if (i != (num / i))
                sum += (num / i);
        }
    }
    return sum;
}

int is_amicable(int num){
    int sum1 = sum_of_div(num);
    return (sum1 != num) && (sum_of_div(sum1) == num);
}

int find_amicable(int n){
    int total_sum = 0;
    for (int i = 1; i <= n; ++i){
        if (is_amicable(i)){
            total_sum += i;
        }
    }
    return total_sum;
}

int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of all amicable numbers from 1 to %d is: %d", n, find_amicable(n));
    return 0;
}