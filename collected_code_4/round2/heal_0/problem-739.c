#include<stdio.h>
#include<math.h>

long long findSmallestTriangular(int n) {
    long long i = 1;
    
    while(1){
        long long triangleNum = (i * (i+1)) / 2;
        int digitCount = floor(log10(triangleNum))+1;

        if(digitCount == n){
            break;
        }
        i++;
    }
    return i;
}

int main(){
    int n;
    printf("Enter number of digits: ");
    scanf("%d", &n);

    long long smallestTriangular = findSmallestTriangular(n);
    printf("Smallest triangular number with %d digits is at index: %lld\n", n, smallestTriangular);
    
    return 0;
}