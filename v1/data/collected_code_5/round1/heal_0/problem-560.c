#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 40

int* findUnion(int arr1[], int arr2[], int len1, int len2, int *unionLen) {
    int *unionArray = malloc(MAX_SIZE * sizeof(int));
    int i, j, k = 0;
    
    if(unionArray == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < len1; i++) {
        unionArray[k] = arr1[i];
        k++;
    }

    for (i = 0; i < len2; i++) {
        int found = 0;
        for (j = 0; j < len1; j++) {
            if (arr2[i] == arr1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unionArray[k] = arr2[i];
            k++;
        }
    }
    *unionLen = k;
    return unionArray;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 8};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    int unionLen = 0;

    int *unionArray = findUnion(arr1, arr2, len1, len2, &unionLen);

    for (int i = 0; i < unionLen; i++) {
        printf("%d ", unionArray[i]);
    }

    printf("\n");
    free(unionArray);
    return 0;
}