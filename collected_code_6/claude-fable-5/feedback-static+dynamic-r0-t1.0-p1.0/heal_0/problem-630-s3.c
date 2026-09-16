#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int x;
    int y;
} Coordinate;

int get_adjacent_coordinates(Coordinate center, int min_x, int max_x,
                             int min_y, int max_y, Coordinate *out,
                             size_t out_capacity, size_t *out_count)
{
    static const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };
    size_t count = 0;
    size_t i;

    if (out == NULL || out_count == NULL) {
        return -1;
    }
    if (min_x > max_x || min_y > max_y) {
        return -1;
    }

    for (i = 0; i < 8; i++) {
        int nx;
        int ny;

        if ((offsets[i][0] < 0 && center.x < min_x - offsets[i][0]) ||
            (offsets[i][0] > 0 && center.x > max_x - offsets[i][0])) {
            continue;
        }
        if ((offsets[i][1] < 0 && center.y < min_y - offsets[i][1]) ||
            (offsets[i][1] > 0 && center.y > max_y - offsets[i][1])) {
            continue;
        }

        nx = center.x + offsets[i][0];
        ny = center.y + offsets[i][1];

        if (count >= out_capacity) {
            return -1;
        }
        out[count].x = nx;
        out[count].y = ny;
        count++;
    }

    *out_count = count;
    return 0;
}

int main(void)
{
    Coordinate center;
    Coordinate *neighbors;
    size_t count = 0;
    size_t i;
    int result;

    center.x = 0;
    center.y = 5;

    neighbors = malloc(8 * sizeof(*neighbors));
    if (neighbors == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = get_adjacent_coordinates(center, 0, 9, 0, 9,
                                      neighbors, 8, &count);
    if (result != 0) {
        fprintf(stderr, "Failed to compute adjacent coordinates\n");
        free(neighbors);
        return EXIT_FAILURE;
    }

    printf("Adjacent coordinates of (%d, %d):\n", center.x, center.y);
    for (i = 0; i < count; i++) {
        printf("(%d, %d)\n", neighbors[i].x, neighbors[i].y);
    }

    free(neighbors);
    return EXIT_SUCCESS;
}