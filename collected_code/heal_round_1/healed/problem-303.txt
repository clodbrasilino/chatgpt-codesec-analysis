#include <stdio.h>

int countInversions(const int arr[], int n){
    int count = 0;
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]>arr[j]){
                count++;
            }
        }
    }
    return count;
}

int isCountOfInversionsEqual(const int arr1[], int n1, const int arr2[], int n2){
    int count1 = countInversions(arr1, n1);
    int count2 = countInversions(arr2, n2);
    if(count1 == count2){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    int arr1[] = {1, 3, 5, 2, 4, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {8, 7, 6, 5, 4, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    if(isCountOfInversionsEqual(arr1, n1, arr2, n2)){
        printf("The count of inversions for the two arrays is the same.\n");
    }
    else{
        printf("The count of inversions for the two arrays is different.\n");
    }
    return 0;
}