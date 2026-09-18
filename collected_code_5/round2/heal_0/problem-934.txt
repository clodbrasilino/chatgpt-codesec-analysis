#include <stdio.h>

// Function to find nth Delannoy number
int delannoy(int n, int m){
    if (m == 0 || n == 0){
        return 1;
    }
    return delannoy(n-1, m) + delannoy(n-1, m-1) + delannoy(n, m-1);
}

// Main function
int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Delannoy number is: %d", n, delannoy(n, n));
    return 0;
}