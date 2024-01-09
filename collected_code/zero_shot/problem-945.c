#include <stdio.h>

void convertToSet(int arr[], int size) {
    int i, j, k;
    
    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                for(k = j; k < size - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                size--;
                j--;
            }
        }
    }
    
    printf("Set: {");
    for(i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if(i != size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 3, 2, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    convertToSet(arr, size);

    return 0;
}