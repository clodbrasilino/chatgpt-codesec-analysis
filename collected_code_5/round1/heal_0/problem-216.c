#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isSubset(int a1[], int a2[], int m, int n) 
{ 
    int i = 0;
    int j = 0;
    for (i = 0; i < n; i++) 
    { 
        for (j = 0; j < m; j++) 
        { 
        if(a2[i] == a1[j]) 
            break; 
        } 
        if (j == m) 
            return false; 
    }
    return true; 
}

void testSubset() {
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int arr2[] = {11, 3, 7, 1};
    int m = sizeof(arr1)/sizeof(arr1[0]);
    int n = sizeof(arr2)/sizeof(arr2[0]);

    if(isSubset(arr1, arr2, m, n))
        printf("arr2[] is subset of arr1[] \n");
    else
        printf("arr2[] is not a subset of arr1[] \n");
}

int main(){
    testSubset();
    return 0;
}