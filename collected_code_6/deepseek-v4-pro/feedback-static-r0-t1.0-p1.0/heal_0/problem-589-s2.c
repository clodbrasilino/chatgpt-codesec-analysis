#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_perfect_squares(int start, int end, int **squares, int *count) {
    if (start > end || squares == NULL || count == NULL) {
        return -1;
    }
    
    int capacity = 10;
    *squares = (int *)malloc(capacity * sizeof(int));
    if (*squares == NULL) {
        return -1;
    }
    
    *count = 0;
    int lower_bound = (int)ceil(sqrt((double)start));
    int upper_bound = (int)floor(sqrt((double)end));
    
    for (int i = lower_bound; i <= upper_bound; i++) {
        int square = i * i;
        if (square >= start && square <= end) {
            if (*count >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(*squares, capacity * sizeof(int));
                if (temp == NULL) {
                    free(*squares);
                    *squares = NULL;
                    *count = 0;
                    return -1;
                }
                *squares = temp;
            }
            (*squares)[*count] = square;
            (*count)++;
        }
    }
    
    return 0;
}

int main(void) {
    int start = 1;
    int end = 100;
    int *squares = NULL;
    int count = 0;
    
    if (find_perfect_squares(start, end, &squares, &count) != 0) {
        printf("Error finding perfect squares\n");
        return 1;
    }
    
    printf("Perfect squares between %d and %d:\n", start, end);
    for (int i = 0; i < count; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");
    
    free(squares);
    return 0;
}