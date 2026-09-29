#include <stdio.h>

/* Possible weaknesses found:
 *  declared here
 */
void reverseArray(int arr[], int pos) {
    int start = 0;
    int end = pos-1;
    int temp;

    /* Possible weaknesses found:
     *  'sizeof' on array function parameter 'arr' will return size of 'int *' [-Wsizeof-array-argument]
     */
    if(pos<0 || pos>sizeof(arr)/sizeof(arr[0])) {
        printf("Invalid position given.");
        return;
    }

    while (start<end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int array[] = { 1, 2, 3, 4, 5, 6 };
    int position = 5;
    int i, num_elements = sizeof(array) / sizeof(array[0]);

    reverseArray(array, position);

    for(i = 0; i < num_elements; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}