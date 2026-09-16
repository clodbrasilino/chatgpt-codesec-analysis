#include <stdio.h>
#include <stdlib.h>

int choose_points(int start1, int end1, int start2, int end2, int **points, int *count) {
    int i;
    int total_points = 0;
    int *result = NULL;
    int index = 0;

    if (start1 > end1 || start2 > end2) {
        return -1;
    }

    if (end1 < start2 || end2 < start1) {
        total_points = (end1 - start1 + 1) + (end2 - start2 + 1);
    } else {
        int overlap_start = (start1 > start2) ? start1 : start2;
        int overlap_end = (end1 < end2) ? end1 : end2;
        int overlap_size = overlap_end - overlap_start + 1;
        total_points = (end1 - start1 + 1) + (end2 - start2 + 1) - overlap_size;
    }

    result = (int *)malloc(total_points * sizeof(int));
    if (result == NULL) {
        return -1;
    }

    for (i = start1; i <= end1; i++) {
        if (i < start2 || i > end2) {
            result[index++] = i;
        }
    }

    for (i = start2; i <= end2; i++) {
        if (i < start1 || i > end1) {
            result[index++] = i;
        }
    }

    *points = result;
    *count = index;
    return 0;
}

int main() {
    int start1 = 1, end1 = 5;
    int start2 = 4, end2 = 8;
    int *points = NULL;
    int count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    if (choose_points(start1, end1, start2, end2, &points, &count) == 0) {
        printf("Chosen points: ");
        for (i = 0; i < count; i++) {
            printf("%d ", points[i]);
        }
        printf("\n");
        free(points);
    } else {
        printf("Error in choosing points\n");
    }

    return 0;
}