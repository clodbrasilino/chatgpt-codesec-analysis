#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }
    
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = 2 * i + 1;
    }
    
    int count = n;
    int step = 2;
    
    while (step <= count) {
        int new_count = 0;
        for (int i = 0; i < count; i++) {
            if ((i + 1) % step != 0) {
                arr[new_count] = arr[i];
                new_count++;
            }
        }
        count = new_count;
        step++;
    }
    
    for (int i = 0; i < count && i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    print_lucky_numbers(n);
    return 0;
}