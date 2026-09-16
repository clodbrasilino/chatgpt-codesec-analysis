#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findMinimumOperations(int a, int b) {
    if (a == b) {
        return 0;
    }

    bool *visited = (bool *)calloc(10001, sizeof(bool));
    if (!visited) {
        return -1;
    }

    int *queue = (int *)malloc(10001 * sizeof(int));
    if (!queue) {
        free(visited);
        return -1;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = a;
    visited[a] = true;

    int operations = 0;

    while (front < rear) {
        int levelSize = rear - front;

        for (int i = 0; i < levelSize; i++) {
            int current = queue[front++];

            if (current == b) {
                free(visited);
                free(queue);
                return operations;
            }

            int next_mul = current * 2;
            if (next_mul <= 10000 && !visited[next_mul]) {
                visited[next_mul] = true;
                queue[rear++] = next_mul;
            }

            int next_sub = current - 1;
            if (next_sub >= 0 && !visited[next_sub]) {
                visited[next_sub] = true;
                queue[rear++] = next_sub;
            }
        }
        operations++;
    }

    free(visited);
    free(queue);
    return -1;
}

int main() {
    int a = 2;
    int b = 10;
    
    int result = findMinimumOperations(a, b);
    
    if (result != -1) {
        printf("Min operations: %d\n", result);
    } else {
        printf("Cannot reach target.\n");
    }

    return 0;
}