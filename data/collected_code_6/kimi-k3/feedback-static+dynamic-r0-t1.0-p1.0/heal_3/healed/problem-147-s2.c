#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define MAX_ROWS 1000
#define MAX_LINE 65536

int max_path_sum(int **triangle, int num_rows) {
    if (triangle == NULL || num_rows <= 0) {
        return INT_MIN;
    }

    int *dp = malloc((size_t)num_rows * sizeof(int));
    if (dp == NULL) {
        return INT_MIN;
    }

    for (int j = 0; j < num_rows; j++) {
        dp[j] = triangle[num_rows - 1][j];
    }

    for (int i = num_rows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int left = dp[j];
            int right = dp[j + 1];
            dp[j] = triangle[i][j] + (left > right ? left : right);
        }
    }

    int result = dp[0];
    free(dp);
    dp = NULL;
    return result;
}

static void free_triangle(int **triangle, int num_rows) {
    if (triangle != NULL) {
        for (int i = 0; i < num_rows; i++) {
            free(triangle[i]);
            triangle[i] = NULL;
        }
        free(triangle);
    }
}

static int read_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return -1;
    }
    
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }
    
    size_t len = strlen(buffer);
    if (len == 0) {
        return -1;
    }
    
    if (buffer[len - 1] != '\n' && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -2;
    }
    return 0;
}

static int parse_long_safe(const char *str, char **endptr, long *result) {
    if (str == NULL || endptr == NULL || result == NULL) {
        return -1;
    }
    
    errno = 0;
    *result = strtol(str, endptr, 10);
    
    if (errno == ERANGE) {
        return -2;
    }
    
    if (*endptr == str) {
        return -3;
    }
    
    return 0;
}

int main(void) {
    char line[MAX_LINE];
    int **triangle = NULL;
    int num_rows = 0;

    int read_status = read_line(line, sizeof(line));
    if (read_status == -1) {
        fprintf(stderr, "Error: No input provided\n");
        return EXIT_FAILURE;
    }
    if (read_status == -2) {
        fprintf(stderr, "Error: Input line too long\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    long rows;
    int parse_result = parse_long_safe(line, &endptr, &rows);
    
    if (parse_result != 0 || rows <= 0 || rows > MAX_ROWS) {
        fprintf(stderr, "Error: Invalid number of rows\n");
        return EXIT_FAILURE;
    }
    num_rows = (int)rows;

    triangle = calloc((size_t)num_rows, sizeof(int *));
    if (triangle == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_rows; i++) {
        read_status = read_line(line, sizeof(line));
        if (read_status == -1) {
            fprintf(stderr, "Error: Unexpected end of input at row %d\n", i + 1);
            free_triangle(triangle, num_rows);
            return EXIT_FAILURE;
        }
        if (read_status == -2) {
            fprintf(stderr, "Error: Input line too long at row %d\n", i + 1);
            free_triangle(triangle, num_rows);
            return EXIT_FAILURE;
        }

        triangle[i] = malloc((size_t)(i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for row %d\n", i + 1);
            free_triangle(triangle, num_rows);
            return EXIT_FAILURE;
        }

        char *ptr = line;
        for (int j = 0; j <= i; j++) {
            while (*ptr == ' ' || *ptr == '\t') {
                ptr++;
            }
            if (*ptr == '\0' || *ptr == '\n') {
                fprintf(stderr, "Error: Insufficient values in row %d\n", i + 1);
                free_triangle(triangle, num_rows);
                return EXIT_FAILURE;
            }
            
            long val;
            parse_result = parse_long_safe(ptr, &endptr, &val);
            
            if (parse_result != 0 || val < INT_MIN || val > INT_MAX) {
                fprintf(stderr, "Error: Invalid value at row %d, column %d\n", i + 1, j + 1);
                free_triangle(triangle, num_rows);
                return EXIT_FAILURE;
            }
            triangle[i][j] = (int)val;
            ptr = endptr;
        }
    }

    int result = max_path_sum(triangle, num_rows);
    if (result == INT_MIN) {
        fprintf(stderr, "Error: Computation failed\n");
        free_triangle(triangle, num_rows);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free_triangle(triangle, num_rows);
    return EXIT_SUCCESS;
}