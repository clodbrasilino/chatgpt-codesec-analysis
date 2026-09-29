#include<stdio.h>
#include<stdbool.h>

bool isDistinct(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    printf("Enter no of elements in tuple: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements of tuple: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if(isDistinct(arr, n)) {
        printf("Tuple is Distinct\n");
    } else {
        printf("Tuple is Not Distinct\n");
    }

    return 0;
}