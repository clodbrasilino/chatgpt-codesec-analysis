#include <stdio.h>

struct Triplet {
    int a;
    int b;
    int c;
    int is_valid;
};

int min_val(int x, int y) {
    return x < y ? x : y;
}

int max_val(int x, int y) {
    return x > y ? x : y;
}

struct Triplet find_three_closest(int arr1[], int n1, int arr2[], int n2, int arr3[], int n3) {
    struct Triplet result = {0, 0, 0, 0};
    
    if (n1 <= 0 || n2 <= 0 || n3 <= 0) {
        return result;
    }

    int i = 0;
    int j = 0;
    int k = 0;

    int current_min = min_val(arr1[i], min_val(arr2[j], arr3[k]));
    int current_max = max_val(arr1[i], max_val(arr2[j], arr3[k]));
    int min_diff = current_max - current_min;

    result.a = arr1[i];
    result.b = arr2[j];
    result.c = arr3[k];
    result.is_valid = 1;

    while (i < n1 && j < n2 && k < n3) {
        current_min = min_val(arr1[i], min_val(arr2[j], arr3[k]));
        current_max = max_val(arr1[i], max_val(arr2[j], arr3[k]));
        int current_diff = current_max - current_min;

        if (current_diff < min_diff) {
            min_diff = current_diff;
            result.a = arr1[i];
            result.b = arr2[j];
            result.c = arr3[k];

            if (min_diff == 0) {
                break;
            }
        }

        if (arr1[i] == current_min) {
            i++;
        } else if (arr2[j] == current_min) {
            j++;
        } else {
            k++;
        }
    }

    return result;
}

int main() {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    struct Triplet res = find_three_closest(arr1, n1, arr2, n2, arr3, n3);

    if (res.is_valid) {
        printf("Closest elements: %d, %d, %d\n", res.a, res.b, res.c);
    } else {
        printf("Invalid input arrays.\n");
    }

    return 0;
}