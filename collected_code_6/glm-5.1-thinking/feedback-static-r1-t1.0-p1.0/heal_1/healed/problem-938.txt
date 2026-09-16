#include <stdio.h>
#include <limits.h>

int find_closest(const int A[], int n1, const int B[], int n2, const int C[], int n3, int *res_a, int *res_b, int *res_c) {
    if (n1 <= 0 || n2 <= 0 || n3 <= 0 || res_a == NULL || res_b == NULL || res_c == NULL) {
        return -1;
    }

    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;

    while (i < n1 && j < n2 && k < n3) {
        int min_val = A[i];
        if (B[j] < min_val) min_val = B[j];
        if (C[k] < min_val) min_val = C[k];

        int max_val = A[i];
        if (B[j] > max_val) max_val = B[j];
        if (C[k] > max_val) max_val = C[k];

        int diff = max_val - min_val;

        if (diff < min_diff) {
            min_diff = diff;
            *res_a = A[i];
            *res_b = B[j];
            *res_c = C[k];

            if (min_diff == 0) {
                break;
            }
        }

        if (min_val == A[i]) {
            i++;
        } else if (min_val == B[j]) {
            j++;
        } else {
            k++;
        }
    }

    return 0;
}

int main(void) {
    int A[] = {1, 4, 10};
    int B[] = {2, 15, 20};
    int C[] = {10, 12};
    int n1 = sizeof(A) / sizeof(A[0]);
    int n2 = sizeof(B) / sizeof(B[0]);
    int n3 = sizeof(C) / sizeof(C[0]);
    int a, b, c;

    if (find_closest(A, n1, B, n2, C, n3, &a, &b, &c) == 0) {
        printf("%d %d %d\n", a, b, c);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}