#include <stdio.h>

int max(int x, int y){
    return (x > y) ? x : y;
}

int find_max_sum(int arr[], int n){
    int incl = arr[0];
    int excl = 0;
    int excl_new;

    for (int i = 1; i < n; i++){
        excl_new = max(incl, excl);
        incl = excl + arr[i];
        excl = excl_new;
    }
    return max(incl, excl);
}

int main(){
    int arr[] = {5, 15, 10, 100, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", find_max_sum(arr, n));
    return 0;
}