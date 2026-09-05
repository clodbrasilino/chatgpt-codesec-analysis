#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

int choose_points(int a1, int a2, int b1, int b2, struct Point **out_points, int *out_count) {
    if (a1 > a2 || b1 > b2) {
        *out_points = NULL;
        *out_count = 0;
        return -1;
    }

    int count = 0;
    int capacity = 2;
    struct Point *points = malloc(capacity * sizeof(struct Point));
    if (!points) {
        return -1;
    }

    for (int i = a1; i <= a2; i++) {
        if (i < b1 || i > b2) {
            if (count >= capacity) {
                capacity *= 2;
                struct Point *tmp = realloc(points, capacity * sizeof(struct Point));
                if (!tmp) {
                    free(points);
                    return -1;
                }
                points = tmp;
            }
            points[count].x = i;
            points[count].y = 0;
            count++;
        }
    }

    for (int i = b1; i <= b2; i++) {
        if (i < a1 || i > a2) {
            if (count >= capacity) {
                capacity *= 2;
                struct Point *tmp = realloc(points, capacity * sizeof(struct Point));
                if (!tmp) {
                    free(points);
                    return -1;
                }
                points = tmp;
            }
            points[count].x = i;
            points[count].y = 1;
            count++;
        }
    }

    if (count == 0) {
        free(points);
        *out_points = NULL;
        *out_count = 0;
        return 0;
    }

    struct Point *shrunk = realloc(points, count * sizeof(struct Point));
    if (shrunk) {
        points = shrunk;
    }

    *out_points = points;
    *out_count = count;
    return 0;
}

int main() {
    struct Point *points = NULL;
    int count = 0;

    int a1 = 1;
    int a2 = 5;
    int b1 = 4;
    int b2 = 8;

    int ret = choose_points(a1, a2, b1, b2, &points, &count);
    if (ret == 0) {
        for (int i = 0; i < count; i++) {
            printf("Point: %d, Range: %d\n", points[i].x, points[i].y);
        }
        free(points);
    }

    return 0;
}