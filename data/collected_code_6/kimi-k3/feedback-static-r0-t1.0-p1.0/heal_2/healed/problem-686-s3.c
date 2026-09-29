#include <stdio.h>
#include <stdlib.h>

void findFrequency(const int arr[], size_t size) {
    if (size == 0) {
        return;
    }
    
    int *visited = (int *)calloc(size, sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (visited[i] == 1) {
            continue;
        }

        int count = 1;
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }
        printf("%d occurs %d times\n", arr[i], count);
    }

    free(visited);
}

int main(void) {
    int arr[] = {4, 5, 6, 4, 5, 4, 7, 8, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    findFrequency(arr, size);

    return EXIT_SUCCESS;
}