#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VAL 10000

int minOperations(int src, int target) {
    if (src == target) {
        return 0;
    }
    
    if (src <= 0 || target <= 0 || src > MAX_VAL || target > MAX_VAL) {
        return -1;
    }
    
    int visited[MAX_VAL + 1] = {0};
    int queue[MAX_VAL + 1];
    int front = 0;
    int rear = 0;
    int operations = 0;
    
    queue[rear++] = src;
    visited[src] = 1;
    
    while (front < rear) {
        int size = rear - front;
        
        for (int i = 0; i < size; i++) {
            int current = queue[front++];
            
            int next = current * 2;
            if (next == target) {
                return operations + 1;
            }
            if (next <= MAX_VAL && !visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
            
            next = current - 1;
            if (next == target) {
                return operations + 1;
            }
            if (next > 0 && !visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
        }
        
        operations++;
    }
    
    return -1;
}

int main(void) {
    int src, target;
    
    if (scanf("%d %d", &src, &target) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = minOperations(src, target);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}