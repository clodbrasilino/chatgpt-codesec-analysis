#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

int get_adjacent_coordinates(Coordinate center, int min_x, int min_y,
                             int max_x, int max_y, Coordinate *result,
                             size_t result_capacity, size_t *count)
{
    static const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    if (result == NULL || count == NULL) {
        return -1;
    }

    if (result_capacity < 8U) {
        return -1;
    }

    if (min_x > max_x || min_y > max_y) {
        return -1;
    }

    *count = 0U;

    for (size_t i = 0U; i < 8U; i++) {
        long nx = (long)center.x + (long)offsets[i][0];
        long ny = (long)center.y + (long)offsets[i][1];

        if (nx < (long)min_x || nx > (long)max_x) {
            continue;
        }
        if (ny < (long)min_y || ny > (long)max_y) {
            continue;
        }

        result[*count].x = (int)nx;
        result[*count].y = (int)ny;
        (*count)++;
    }

    return 0;
}

int main(void)
{
    Coordinate center = {2, 3};
    Coordinate *neighbors = NULL;
    size_t count = 0U;

    neighbors = malloc(8U * sizeof(Coordinate));
    if (neighbors == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (get_adjacent_coordinates(center, 0, 0, 4, 4, neighbors, 8U, &count) != 0) {
        fprintf(stderr, "Failed to compute adjacent coordinates\n");
        free(neighbors);
        return EXIT_FAILURE;
    }

    printf("Adjacent coordinates of (%d, %d):\n", center.x, center.y);
    for (size_t i = 0U; i < count; i++) {
        printf("(%d, %d)\n", neighbors[i].x, neighbors[i].y);
    }

    free(neighbors);
    neighbors = NULL;

    return EXIT_SUCCESS;
}