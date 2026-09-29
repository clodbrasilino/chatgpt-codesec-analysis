#include <stdio.h>
#include <stdlib.h>

#define FAILURE 1
#define SUCCESS 0

int find_median(const int arr1[], const int arr2[], int n) {
    int i = 0;
    int j = 0;
    int m1 = 0;
    int m2 = 0;
    int count;

    if (n <= 0) {
        fprintf(stderr, "Error: Array size must be positive.\n");
        exit(FAILURE);
    }

    for (count = 0; count <= n; count++) {
        if (i == n) {
            m1 = m2;
            m2 = arr2[j];
            break;
        }
        if (j == n) {
            m1 = m2;
            m2 = arr1[i];
            break;
        }

        if (arr1[i] <= arr2[j]) {
            m1 = m2;
            m2 = arr1[i];
            i++;
        } else {
            m1 = m2;
            m2 = arr2[j];
            j++;
        }
    }

    return (m1 + m2) / 2;
}

int main(void) {
    int arr1[] = {1, 12, 15, 26, 38};
    int arr2[] = {2, 13, 17, 30, 45};
    size_t n = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);

    if (n != n2) {
        fprintf(stderr, "Error: Both arrays must have the same size.\n");
        return FAILURE;
    }

    int median = find_median(arr1, arr2, (int)n);
    printf("Median is %d\n", median);

    return SUCCESS;
}