#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 2
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    if (a == b) return 0;
    
    if (a < 0 || b < 0) return -1;
    
    if (a > INT_MAX / 2 || b > INT_MAX / 2) return -1;
    
    int max_val = (a > b) ? a * 2 : b * 2;
    
    if (max_val > 1000000) {
        max_val = 1000000;
    }
    
    if (max_val < b) max_val = b;
    if (max_val < a) max_val = a;
    
    max_val = max_val * 2 + 4;
    
    int *dp = (int *)malloc((max_val + 1) * sizeof(int));
    if (dp == NULL) return -1;
    
    int *queue = (int *)malloc((max_val + 1) * sizeof(int));
    if (queue == NULL) {
        free(dp);
        return -1;
    }
    
    for (int i = 0; i <= max_val; i++) {
        dp[i] = INT_MAX;
    }
    
    int front = 0, rear = 0;
    
    queue[rear++] = a;
    if (a <= max_val) {
        dp[a] = 0;
    }
    
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
        if (next <= max_val && dp[next] == INT_MAX) {
            dp[next] = current_steps + 1;
            queue[rear++] = next;
        }
        
        next = current - 1;
        if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
            dp[next] = current_steps + 1;
            queue[rear++] = next;
        }
        
        if (current > 0 && current <= INT_MAX / 2) {
            next = current * 2;
            if (next <= max_val && dp[next] == INT_MAX) {
                dp[next] = current_steps + 1;
                queue[rear++] = next;
            }
        }
        
        if (current > 0 && current % 2 == 0) {
            next = current / 2;
            if (next <= max_val && dp[next] == INT_MAX) {
                dp[next] = current_steps + 1;
                queue[rear++] = next;
            }
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