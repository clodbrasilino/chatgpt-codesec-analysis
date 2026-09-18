#include<stdio.h>
#include<stdlib.h>

int minJumps(int arr[], int n){
    if (n <= 1)
        return 0;
    if (arr[0] == 0)
        return -1;

    int maxReach = arr[0];
    int step = arr[0];
    int jump = 1;

    for (int i = 1; i < n; i++){
        if (i == n-1)
            return jump;
       
        /* Possible weaknesses found:
         *  call to undeclared function 'max'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        maxReach = max(maxReach, i + arr[i]);
        step--;

        if (step == 0){
            jump++;
            if(i >= maxReach)
                return -1;
            step = maxReach - i;
        }
    }

    return -1;
}

int max(int x, int y)
{
    return (x > y)? x: y;
}

int main(){

    int arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int size = sizeof(arr)/sizeof(int);
   
    int result = minJumps(arr, size);
    if(result == -1){
        printf("Sorry, jump is not possible\n");
        return 0;
    }

    printf("Minimum number of jumps to reach end is %d \n", minJumps(arr,size));

    return 0;
}