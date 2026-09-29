#include <stdio.h>

int equilibrium_index(int arr[], int n) {
    if (n <= 0) {
        return -1;
    }

    long long total_sum = 0;
    long long left_sum = 0;

    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    for (int i = 0; i < n; i++) {
        total_sum -= arr[i];

        if (left_sum == total_sum) {
            return i;
        }

        left_sum += arr[i];
    }

    return -1;
}

int main(void) {
    int arr1[] = {-7, 1, 5, 2, -4, 3, 0};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int eq1 = equilibrium_index(arr1, n1);
    printf("Equilibrium index: %d\n", eq1);

    int arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int eq2 = equilibrium_index(arr2, n2);
    printf("Equilibrium index: %d\n", eq2);

    int arr3[] = {0, 0, 0, 0};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int eq3 = equilibrium_index(arr3, n3);
    printf("Equilibrium index: %d\n", eq3);

    int arr4[] = {5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int eq4 = equilibrium_index(arr4, n4);
    printf("Equilibrium index: %d\n", eq4);

    int arr5[] = {1, -1, 0};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    int eq5 = equilibrium_index(arr5, n5);
    printf("Equilibrium index: %d\n", eq5);

    return 0;
}