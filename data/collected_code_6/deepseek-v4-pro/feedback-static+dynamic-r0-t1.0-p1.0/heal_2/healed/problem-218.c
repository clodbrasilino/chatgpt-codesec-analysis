#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_operations(int a, int b) {
    if (a == b) return 0;
    
    if (a < 0 || b < 0) return -1;
    
    int max_bound = (a > b ? a : b) * 2;
    if (max_bound < 0) {
        max_bound = INT_MAX / 4;
    }
    
    if (max_bound > 1000000) {
        max_bound = 1000000;
    }
    
    int max_val = max_bound + 100;
    
    int *dp = (int *)malloc((max_val + 1) * sizeof(int));
    if (dp == NULL) return -1;
    
    for (int i = 0; i <= max_val; i++) {
        dp[i] = INT_MAX;
    }
    
    int *queue = (int *)malloc((max_val + 1) * sizeof(int));
    if (queue == NULL) {
        free(dp);
        return -1;
    }
    
    int front = 0, rear = 0;
    queue[rear++] = a;
    dp[a] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        int current_steps = dp[current];
        
        if (current == b) {
            free(dp);
            free(queue);
            return current_steps;
        }
        
        int next;
        
        next = current + 1;
        if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
            dp[next] = current_steps + 1;
            queue[rear++] = next;
        }
        
        next = current - 1;
        if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
            dp[next] = current_steps + 1;
            queue[rear++] = next;
        }
        
        if (current > 0 && current <= max_val / 2) {
            next = current * 2;
            if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
                dp[next] = current_steps + 1;
                queue[rear++] = next;
            }
        }
        
        if (current > 0 && current % 2 == 0) {
            next = current / 2;
            if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
                dp[next] = current_steps + 1;
                queue[rear++] = next;
            }
        }
        
        if (rear > max_val - 4) {
            int new_max = max_val * 2;
            if (new_max > 2000000) {
                break;
            }
            int *new_dp = (int *)realloc(dp, (new_max + 1) * sizeof(int));
            if (new_dp == NULL) {
                free(dp);
                free(queue);
                return -1;
            }
            dp = new_dp;
            
            int *new_queue = (int *)realloc(queue, (new_max + 1) * sizeof(int));
            if (new_queue == NULL) {
                free(dp);
                free(queue);
                return -1;
            }
            queue = new_queue;
            
            for (int i = max_val + 1; i <= new_max; i++) {
                dp[i] = INT_MAX;
            }
            max_val = new_max;
        }
    }
    
    free(dp);
    free(queue);
    return -1;
}

int main(void) {
    int a, b;
    
    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }
    
    int result = min_operations(a, b);
    printf("%d\n", result);
    
    return 0;
}