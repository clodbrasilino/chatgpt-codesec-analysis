#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
} Range;

bool is_in_range(int point, Range r) {
    return point >= r.start && point <= r.end;
}

bool is_valid_point(int point, Range r1, Range r2) {
    bool in_r1 = is_in_range(point, r1);
    bool in_r2 = is_in_range(point, r2);
    
    if (in_r1 && in_r2) {
        return false;
    }
    return in_r1 || in_r2;
}

int choose_points(Range r1, Range r2, int *points, size_t max_points) {
    if (points == NULL || max_points == 0) {
        return -1;
    }
    
    if (r1.start > r1.end || r2.start > r2.end) {
        return -1;
    }
    
    size_t count = 0;
    
    for (int i = r1.start; i <= r1.end && count < max_points; i++) {
        if (is_valid_point(i, r1, r2)) {
            points[count] = i;
            count++;
        }
    }
    
    for (int i = r2.start; i <= r2.end && count < max_points; i++) {
        if (is_valid_point(i, r1, r2)) {
            points[count] = i;
            count++;
        }
    }
    
    return (int)count;
}

int main(void) {
    Range range1 = {1, 10};
    Range range2 = {5, 15};
    int points[20];
    
    int result = choose_points(range1, range2, points, 20);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }
    
    printf("Selected %d points:\n", result);
    for (int i = 0; i < result; i++) {
        printf("%d ", points[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}