/* Possible weaknesses found:
 *  stray '`' in program
 */
```
#include <stdio.h>
#include <stdlib.h>

#define MAX 2500

int deleteElements(int a[], int arr_size, int k) {
    if (k > arr_size)
        return arr_size;
    if (k <= 0)
        return arr_size;

    int i;
    int j = 0; 
    int counter; 

    for(counter =1; counter<=arr_size; counter++) {
        if(counter % k != 0) {
            a[j] = a[counter];
            j++;
        }
    }
    return j; 
}

void findLucky(int arr[], int size) {
    int ptr = 1;

    int arr_size = size;
  
    while(ptr != arr_size) {
        arr_size = deleteElements(arr, arr_size, ptr);
        if(ptr >= arr_size)
            break;
        ptr++;
    }
}

int luckyNos(int n) {
    if(n > MAX) {
        printf("Out of bounds\n");
        exit(0);
    }
    int arr[MAX];
  
    int i;
    for (i = 0; i < MAX; i++)
        arr[i] = i+1;

    findLucky(arr, MAX);
  
    return arr[n-1];
}

int main() {
    int n;
    printf("Enter the nth lucky number to get: ");
    scanf("%d", &n);
    printf("%dth lucky number is %d\n", n, luckyNos(n));
    return 0;
}