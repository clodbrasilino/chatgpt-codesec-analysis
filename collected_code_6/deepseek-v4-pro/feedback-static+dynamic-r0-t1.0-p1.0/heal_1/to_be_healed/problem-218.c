#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 2
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    if (a == b) return 0;
    
    int max_val = (a > b ? a : b) * 2;
    int *dp = (int *)malloc((max_val + 1) * sizeof(int));
    if (dp == NULL) exit(1);
    
    for (int i = 0; i <= max_val; i++) {
        dp[i] = INT_MAX;
    }
    
    dp[a] = 0;
    int *queue = (int *)malloc((max_val + 1) * sizeof(int));
    if (queue == NULL) {
        free(dp);
        exit(1);
    }
    
    int front = 0, rear = 0;
    queue[rear++] = a;
    
    while (front < rear) {
        int current = queue[front++];
        
        if (current == b) {
            int result = dp[current];
            free(dp);
            free(queue);
            return result;
        }
        
        int next_vals[4];
        int next_count = 0;
        next_vals[next_count++] = current + 1;
        next_vals[next_count++] = current - 1;
        if (current <= max_val / 2) {
            next_vals[next_count++] = current * 2;
        }
        if (current % 2 == 0) {
            next_vals[next_count++] = current / 2;
        }
        
        for (int i = 0; i < next_count; i++) {
            int next = next_vals[i];
            if (next >= 0 && next <= max_val && dp[next] == INT_MAX) {
                dp[next] = dp[current] + 1;
                queue[rear++] = next;
            }
        }
    }
    
    int result = -1;
    free(dp);
    free(queue);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:27013,execs:376,op:havoc,rep:7; likely memory-safety defect
  */

int main(void) {
    int a, b;
    
    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }
    
    int result = min_operations(a, b);
    printf("%d\n", result);
    
    return 0;
}