#include <stdio.h>
#include <stdlib.h>

int* find_max_subsets(int n, int* arr) {
    int *subset_counts = (int*)malloc(n * sizeof(int));
    int *result = (int*)malloc(n * sizeof(int));

    if(subset_counts == NULL || result == NULL) {
        return NULL;
    }

    for(int i=0; i<n; i++) {
        subset_counts[i] = 0;
    }

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[j] % arr[i] == 0)
                subset_counts[i]++;
        }
    }

    int max_index = 0;
    for(int i=1; i<n; i++) {
        if(subset_counts[i] > subset_counts[max_index]) 
            max_index = i;
    }

    int count = 0;
    for(int i=max_index; i<n; i++) {
        if(arr[i] % arr[max_index] == 0) {
            result[count] = arr[i];
            count++;
        }
    }
    free(subset_counts);
    return result;
}

int main() {
    int n;
    printf("Enter how many elements you want to have in your set:\n");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));

    printf("\nEnter array elements:\n");
    for(int i=0; i<n; i++) 
        scanf("%d", &arr[i]);
    
    int* result = find_max_subsets(n, arr);

    if(result == NULL) {
        printf("Memory allocation failure!\n");
        return 1;
    }

    printf("\nLargest subset where each pair is divisible is:\n");
    for(int i=0; i<n; i++) {
        if(result[i] == 0)
            break;
        printf("%d ", result[i]);
    }

    free(arr);
    free(result);

    return 0;
}