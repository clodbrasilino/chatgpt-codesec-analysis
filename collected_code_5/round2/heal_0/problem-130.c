#include<stdio.h>
#define ARRAY_SIZE 100

int get_maximum_frequency(int arr[], int n) {
    int max_count = 0, res = arr[0], curr_count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1])
            curr_count++;
        else {
            if (curr_count > max_count) {
                max_count = curr_count;
                res = arr[i - 1];
            }
            curr_count = 1;
        }
    }

    if (curr_count > max_count) {
        max_count = curr_count;
        res = arr[n - 1];
    }

    return res;
}

void sort(int a[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++)
          if (a[j] < a[min])
            min = j;

        temp = a[min];
        a[min] = a[i];
        a[i] = temp;
    }
}

int main() {
    int arr[ARRAY_SIZE];
    int n, i;
   
    printf("Enter size of the array : ");
    scanf("%d", &n);

    printf("Enter elements in array : ");
    for(i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    sort(arr, n);

    printf("The item with maximum frequency is %d ", get_maximum_frequency(arr, n));
    return 0;
}