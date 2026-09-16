#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    int *points;
    int count;
} PointSet;

/* Possible weaknesses found:
 *  Parameter 'range2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'range1' can be declared as pointer to const [constParameterPointer]
 */
PointSet choose_points(Range *range1, Range *range2) {
    PointSet result;
    result.points = NULL;
    result.count = 0;

    if (range1 == NULL || range2 == NULL) {
        return result;
    }

    if (range1->start > range1->end || range2->start > range2->end) {
        return result;
    }

    if (range1->end < range2->start || range2->end < range1->start) {
        result.count = 2;
        result.points = (int *)malloc(result.count * sizeof(int));
        if (result.points == NULL) {
            result.count = 0;
            return result;
        }
        result.points[0] = range1->end;
        result.points[1] = range2->end;
        return result;
    }

    if (range1->start < range2->start) {
        result.count = 2;
        result.points = (int *)malloc(result.count * sizeof(int));
        if (result.points == NULL) {
            result.count = 0;
            return result;
        }
        result.points[0] = range1->start;
        result.points[1] = range2->end;
        return result;
    } else {
        result.count = 2;
        result.points = (int *)malloc(result.count * sizeof(int));
        if (result.points == NULL) {
            result.count = 0;
            return result;
        }
        result.points[0] = range1->end;
        result.points[1] = range2->start;
        return result;
    }
}

int main(void) {
    Range r1 = {1, 5};
    Range r2 = {3, 8};
    PointSet ps = choose_points(&r1, &r2);

    if (ps.points != NULL && ps.count > 0) {
        for (int i = 0; i < ps.count; i++) {
            printf("%d ", ps.points[i]);
        }
        printf("\n");
        free(ps.points);
    }

    Range r3 = {10, 15};
    Range r4 = {20, 25};
    PointSet ps2 = choose_points(&r3, &r4);

    if (ps2.points != NULL && ps2.count > 0) {
        for (int i = 0; i < ps2.count; i++) {
            printf("%d ", ps2.points[i]);
        }
        printf("\n");
        free(ps2.points);
    }

    Range r5 = {5, 10};
    Range r6 = {1, 7};
    PointSet ps3 = choose_points(&r5, &r6);

    if (ps3.points != NULL && ps3.count > 0) {
        for (int i = 0; i < ps3.count; i++) {
            printf("%d ", ps3.points[i]);
        }
        printf("\n");
        free(ps3.points);
    }

    return 0;
}