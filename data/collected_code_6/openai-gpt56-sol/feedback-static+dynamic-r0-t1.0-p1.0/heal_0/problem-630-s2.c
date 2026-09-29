#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

static int get_adjacent_coordinates(Coordinate center,
                                    Coordinate **neighbors,
                                    size_t *count)
{
    static const int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1,  0},          {1,  0},
        {-1,  1}, {0,  1}, {1,  1}
    };
    Coordinate *result;
    size_t i;

    if (neighbors == NULL || count == NULL) {
        return -1;
    }

    *neighbors = NULL;
    *count = 0;

    result = malloc(8 * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < 8; ++i) {
        result[i].x = center.x + offsets[i][0];
        result[i].y = center.y + offsets[i][1];
    }

    *neighbors = result;
    *count = 8;
    return 0;
}

int main(void)
{
    Coordinate center;
    Coordinate *neighbors = NULL;
    size_t count = 0;
    size_t i;

    if (scanf("%d %d", &center.x, &center.y) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (get_adjacent_coordinates(center, &neighbors, &count) != 0) {
        fputs("Failed to extract adjacent coordinates\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        printf("(%d, %d)\n", neighbors[i].x, neighbors[i].y);
    }

    free(neighbors);
    return EXIT_SUCCESS;
}