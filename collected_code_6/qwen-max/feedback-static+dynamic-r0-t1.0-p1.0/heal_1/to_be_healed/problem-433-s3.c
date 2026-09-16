#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool isGreaterThanAll(int num, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (num <= arr[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int size = sizeof(arr) / sizeof(arr[0]);
    
    if (isGreaterThanAll(num, arr, size)) {
        printf("The entered number is greater than all elements in the array.\n");
    } else {
        printf("The entered number is not greater than all elements in the array.\n");
    }
    
    return 0;
}