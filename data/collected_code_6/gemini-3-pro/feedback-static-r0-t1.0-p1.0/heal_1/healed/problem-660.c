#include <stdio.h>
#include <stdlib.h>

int find_points(int range1_start, int range1_end, int range2_start, int range2_end, int *point1, int *point2) {
    if (point1 == NULL || point2 == NULL) {
        return -1;
    }

    if (range1_start > range1_end || range2_start > range2_end) {
        return -1;
    }

    if (range1_end < range2_start) {
        *point1 = range1_start;
        *point2 = range2_start;
        return 0;
    }

    if (range2_end < range1_start) {
        *point1 = range1_start;
        *point2 = range2_start;
        return 0;
    }

    if (range1_start < range2_start && range1_end <= range2_end) {
        *point1 = range1_start;
        *point2 = range2_end;
        return 0;
    }
    
    if (range2_start < range1_start && range2_end <= range1_end) {
        *point1 = range1_end;
        *point2 = range2_start;
        return 0;
    }

    if (range1_start >= range2_start && range1_end <= range2_end) {
        if (range2_start < range1_start) {
            *point1 = range1_start;
            *point2 = range2_start;
            return 0;
        } else if (range2_end > range1_end) {
            *point1 = range1_end;
            *point2 = range2_end;
            return 0;
        } else {
             return -1;
        }
    }

    if (range2_start >= range1_start && range2_end <= range1_end) {
        if (range1_start < range2_start) {
            *point1 = range1_start;
            *point2 = range2_start;
            return 0;
        } else if (range1_end > range2_end) {
            *point1 = range1_end;
            *point2 = range2_end;
            return 0;
        } else {
            return -1;
        }
    }

    return -1;
}

int main(void) {
    int r1_start = 1;
    int r1_end = 5;
    int r2_start = 4;
    int r2_end = 8;
    int p1 = 0;
    int p2 = 0;

    if (find_points(r1_start, r1_end, r2_start, r2_end, &p1, &p2) == 0) {
        printf("Point 1: %d, Point 2: %d\n", p1, p2);
    } else {
        printf("Could not find suitable points.\n");
    }

    r1_start = 1;
    r1_end = 5;
    r2_start = 6;
    r2_end = 10;
    
    if (find_points(r1_start, r1_end, r2_start, r2_end, &p1, &p2) == 0) {
        printf("Point 1: %d, Point 2: %d\n", p1, p2);
    } else {
        printf("Could not find suitable points.\n");
    }

    r1_start = 2;
    r1_end = 2;
    r2_start = 2;
    r2_end = 2;
    
    if (find_points(r1_start, r1_end, r2_start, r2_end, &p1, &p2) == 0) {
        printf("Point 1: %d, Point 2: %d\n", p1, p2);
    } else {
        printf("Could not find suitable points.\n");
    }

    return 0;
}