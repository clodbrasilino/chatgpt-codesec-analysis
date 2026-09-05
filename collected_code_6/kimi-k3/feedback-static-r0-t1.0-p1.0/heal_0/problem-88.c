#include <stdio.h>
#include <stdlib.h>

void printFrequency(const int *arr, size_t size)
{
    if (arr == NULL || size == 0) {
        printf("List is empty or invalid.\n");
        return;
    }

    int *visited = (int *)calloc(size, sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (visited[i] == 1) {
            continue;
        }

        size_t count = 1;
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }

        printf("%d occurs %zu time%s\n", arr[i], count, (count > 1) ? "s" : "");
    }

    free(visited);
}

int main(void)
{
    int list[] = {4, 2, 2, 8, 3, 3, 3, 4, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);

    printFrequency(list, size);

    return 0;
}