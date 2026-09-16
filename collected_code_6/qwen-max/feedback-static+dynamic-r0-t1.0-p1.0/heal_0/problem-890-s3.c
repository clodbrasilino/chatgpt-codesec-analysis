#include <stdio.h>
#include <stdlib.h>

int findExtraElementIndex(const int *arr1, const int *arr2, int len1, int len2) {
    for (int i = 0; i < len1; ++i) {
        if (arr1[i] != arr2[i]) {
            return i;
        }
    }
    return len1;
}

int main() {
    int arr1[] = {2, 4, 6, 8, 9, 10, 12};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);

    int index = findExtraElementIndex(arr1, arr2, len1, len2);
    printf("The extra element is at index: %d\n", index);

    return 0;
}