#include <stdio.h>

int check_array(int num, int arr[], int size){
    for(int i=0;i<size;i++){
        if(num <= arr[i]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int arr[] = {10,20,30,40,50};
    int num;
    printf("Enter a number: ");
    scanf("%d",&num);

    if(check_array(num, arr, sizeof(arr) / sizeof(arr[0]))){
        printf("The entered number is greater than all the elements of the array.\n");
    } else {
        printf("The entered number is not greater than all the elements of the array.\n");
    }
    return 0;
}