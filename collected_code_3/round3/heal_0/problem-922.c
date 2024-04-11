#include <stdio.h>
#include <stdlib.h>

void find_max_product_pair(int arr[], int n) {
    if (n < 2) {
        printf("No pairs exist\n");
        return;
    }

    int pos_a = 0, pos_b = 0;
    int neg_a = 0, neg_b = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > pos_a) {
            pos_b = pos_a;
            pos_a = arr[i];
        } else if (arr[i] > pos_b) {
            pos_b = arr[i];
        }

        if (arr[i] < 0 && abs(arr[i]) > abs(neg_a)) {
            neg_b = neg_a;
            neg_a = arr[i];
        } else if(arr[i] < 0 && abs(arr[i]) > abs(neg_b)) {
            neg_b = arr[i];
        }
    }

    if (neg_a * neg_b > pos_a * pos_b) {
        printf("Max product pair is {%d, %d}", neg_a, neg_b);
    } else {
        printf("Max product pair is {%d, %d}", pos_a, pos_b);
    }
}

int main() {
    int arr[] = {1, -10, -25, 20, 7, 3, -5, -6};
    int n = sizeof(arr)/sizeof(arr[0]);
    find_max_product_pair(arr, n);
    return 0;
}