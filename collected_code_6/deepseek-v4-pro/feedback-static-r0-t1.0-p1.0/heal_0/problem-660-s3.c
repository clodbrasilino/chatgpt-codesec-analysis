#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    int *points;
    int count;
    int capacity;
} PointSet;

void init_point_set(PointSet *set, int capacity) {
    set->points = (int *)malloc((size_t)capacity * sizeof(int));
    if (set->points == NULL) {
        exit(EXIT_FAILURE);
    }
    set->count = 0;
    set->capacity = capacity;
}

void free_point_set(PointSet *set) {
    free(set->points);
    set->points = NULL;
    set->count = 0;
    set->capacity = 0;
}

int add_point(PointSet *set, int point) {
    if (set->count >= set->capacity) {
        int new_capacity = set->capacity * 2;
        int *new_points = (int *)realloc(set->points, (size_t)new_capacity * sizeof(int));
        if (new_points == NULL) {
            return 0;
        }
        set->points = new_points;
        set->capacity = new_capacity;
    }
    set->points[set->count] = point;
    set->count++;
    return 1;
}

int is_in_range(int point, const Range *range) {
    return point >= range->start && point <= range->end;
}

void choose_points(const Range *range1, const Range *range2, PointSet *set) {
    int i;
    for (i = range1->start; i <= range1->end; i++) {
        if (!is_in_range(i, range2)) {
            if (!add_point(set, i)) {
                free_point_set(set);
                exit(EXIT_FAILURE);
            }
        }
    }
    for (i = range2->start; i <= range2->end; i++) {
        if (!is_in_range(i, range1)) {
            if (!add_point(set, i)) {
                free_point_set(set);
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(void) {
    Range range1 = {1, 5};
    Range range2 = {4, 8};
    PointSet set;
    
    init_point_set(&set, 4);
    choose_points(&range1, &range2, &set);
    
    printf("Chosen points that are in only one range:\n");
    for (int i = 0; i < set.count; i++) {
        printf("%d ", set.points[i]);
    }
    printf("\n");
    
    free_point_set(&set);
    return 0;
}