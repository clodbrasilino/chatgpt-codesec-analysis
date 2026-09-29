#include <stdio.h>
#include <stdlib.h>

void flip(int arr[], int i) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;
    int start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_max(int arr[], int n) {
    int mi = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > arr[mi]) {
            mi = i;
        }
    }
    return mi;
}

void pancake_sort(int *arr, int n) {
    if (arr == NULL || n <= 1) {
        return;
    }
    for (int curr_size = n; curr_size > 1; curr_size--) {
        int mi = find_max(arr, curr_size);
        if (mi != curr_size - 1) {
            if (mi != 0) {
                flip(arr, mi);
            }
            flip(arr, curr_size - 1);
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val > __INT_MAX__ || val < (-__INT_MAX__ - 1)) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }
    pancake_sort(arr, n);
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return EXIT_SUCCESS;
}