#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void find_combinations(int *items, int start, int end, int *buffer, int buffer_index) {
    if (start > end) {
        return;
    }

    for (int i = start; i <= end; i++) {
        buffer[buffer_index] = items[i];
        printf("{");
        for (int j = 0; j <= buffer_index; j++) {
            printf("%d", buffer[j]);
            if (j < buffer_index) {
                printf(", ");
            }
        }
        printf("}\n");

        swap(&items[i], &items[start]);
        find_combinations(items, start + 1, end, buffer, buffer_index + 1);
        swap(&items[i], &items[start]);
    }
}

int main(void) {
    int items[] = {1, 2, 3, 4};
    int n = sizeof(items) / sizeof(items[0]);
    int *buffer = malloc(n * sizeof(int));
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    find_combinations(items, 0, n - 1, buffer, 0);

    free(buffer);
    return 0;
}