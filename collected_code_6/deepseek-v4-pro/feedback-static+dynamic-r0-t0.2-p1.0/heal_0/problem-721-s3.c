#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

static void dfs(int **matrix, int n, int row, int col, int *visited, 
                int *path, int path_len, double *max_avg, int *best_path, int *best_len) {
    visited[row * n + col] = 1;
    path[path_len] = row * n + col;
    path_len++;
    
    int sum = 0;
    for (int i = 0; i < path_len; i++) {
        sum += matrix[path[i] / n][path[i] % n];
    }
    double avg = (double)sum / path_len;
    
    if (avg > *max_avg) {
        *max_avg = avg;
        memcpy(best_path, path, path_len * sizeof(int));
        *best_len = path_len;
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        
        if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < n && 
            !visited[new_row * n + new_col]) {
            dfs(matrix, n, new_row, new_col, visited, path, path_len, 
                max_avg, best_path, best_len);
        }
    }
    
    visited[row * n + col] = 0;
}

double find_max_average_path(int **matrix, int n, int *best_path, int *best_len) {
    int *visited = (int *)calloc(n * n, sizeof(int));
    int *path = (int *)malloc(n * n * sizeof(int));
    int *temp_best = (int *)malloc(n * n * sizeof(int));
    
    if (!visited || !path || !temp_best) {
        free(visited);
        free(path);
        free(temp_best);
        return -DBL_MAX;
    }
    
    double max_avg = -DBL_MAX;
    *best_len = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            memset(visited, 0, n * n * sizeof(int));
            dfs(matrix, n, i, j, visited, path, 0, &max_avg, temp_best, best_len);
        }
    }
    
    if (*best_len > 0) {
        memcpy(best_path, temp_best, *best_len * sizeof(int));
    }
    
    free(visited);
    free(path);
    free(temp_best);
    
    return max_avg;
}

int main(void) {
    int n = 3;
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    
    int data[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = data[i][j];
        }
    }
    
    int *best_path = (int *)malloc(n * n * sizeof(int));
    int best_len = 0;
    
    double max_avg = find_max_average_path(matrix, n, best_path, &best_len);
    
    printf("Maximum average: %.2f\n", max_avg);
    printf("Path length: %d\n", best_len);
    printf("Path: ");
    for (int i = 0; i < best_len; i++) {
        printf("(%d,%d) ", best_path[i] / n, best_path[i] % n);
    }
    printf("\n");
    
    free(best_path);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}