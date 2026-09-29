#include <stdio.h>

#define MAX_SIZE 1000

// function to find intersection of arrays
void findIntersection(int arr1[], int arr2[], int n1, int n2) {
    int i, j;
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            if (arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
}

// main function
int main() {
    int arr1[MAX_SIZE], arr2[MAX_SIZE], n1, n2, i;

    printf("Enter the number of elements in array 1: ");
    scanf("%d", &n1);
    if(n1 > 0 && n1 <= MAX_SIZE) {
        printf("Enter elements in array 1: ");
        for (i = 0; i < n1; i++) {
            scanf("%d", &arr1[i]);
        }
    } else {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter the number of elements in array 2: ");
    scanf("%d", &n2);
    if(n2 > 0 && n2 <= MAX_SIZE) {
        printf("Enter elements in array 2: ");
        for (i = 0; i < n2; i++) {
            scanf("%d", &arr2[i]);
        }
    } else {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Intersection of arrays is:");
    findIntersection(arr1, arr2, n1, n2);
    return 0;
}