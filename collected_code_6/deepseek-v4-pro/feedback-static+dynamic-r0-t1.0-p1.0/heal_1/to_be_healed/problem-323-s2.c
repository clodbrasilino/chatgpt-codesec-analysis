#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void rearrange_array(int arr[], int n) {
    /* Possible weaknesses found:
     *  Variable 'pos_index' is assigned a value that is never used. [unreadVariable]
     */
    int pos_index = 0;
    /* Possible weaknesses found:
     *  Variable 'neg_index' is assigned a value that is never used. [unreadVariable]
     */
    int neg_index = 0;
    int *positives = NULL;
    int *negatives = NULL;
    int pos_count = 0;
    int neg_count = 0;
    int i;
    int pos_ptr = 0;
    int neg_ptr = 0;
    int index = 0;
    
    if (n <= 0) {
        return;
    }
    
    positives = (int*)malloc(n * sizeof(int));
    negatives = (int*)malloc(n * sizeof(int));
    
    if (positives == NULL || negatives == NULL) {
        free(positives);
        free(negatives);
        return;
    }
    
    for (i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            positives[pos_count++] = arr[i];
        } else {
            negatives[neg_count++] = arr[i];
        }
    }
    
    while (pos_ptr < pos_count && neg_ptr < neg_count) {
        arr[index++] = positives[pos_ptr++];
        arr[index++] = negatives[neg_ptr++];
    }
    
    while (pos_ptr < pos_count) {
        arr[index++] = positives[pos_ptr++];
    }
    
    while (neg_ptr < neg_count) {
        arr[index++] = negatives[neg_ptr++];
    }
    
    free(positives);
    free(negatives);
}

int main(void) {
    int arr[MAX_SIZE];
    int n;
    int i;
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input\n");
            return 1;
        }
    }
    
    rearrange_array(arr, n);
    
    printf("Rearranged array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}