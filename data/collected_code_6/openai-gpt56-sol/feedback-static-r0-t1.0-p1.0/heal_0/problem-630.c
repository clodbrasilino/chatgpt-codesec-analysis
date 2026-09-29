#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

static int get_adjacent_coordinates(Coordinate center,
                                    Coordinate **adjacent,
                                    size_t *count)
{
    static const int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1,  0},          {1,  0},
        {-1,  1}, {0,  1}, {1,  1}
    };
    Coordinate *result;
    size_t i;

    if (adjacent == NULL || count == NULL) {
        return -1;
    }

    *adjacent = NULL;
    *count = 0;

    result = malloc(sizeof(*result) * 8U);
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < 8U; ++i) {
        result[i].x = center.x + offsets[i][0];
        result[i].y = center.y + offsets[i][1];
    }

    *adjacent = result;
    *count = 8U;
    return 0;
}

int main(void)
{
    Coordinate center;
    Coordinate *adjacent = NULL;
    size_t count = 0;
    size_t i;

    if (scanf("%d %d", &center.x, &center.y) != 2) {
        fprintf(stderr, "Invalid coordinate input\n");
        return EXIT_FAILURE;
    }

    if (get_adjacent_coordinates(center, &adjacent, &count) != 0) {
        fprintf(stderr, "Unable to extract adjacent coordinates\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        printf("(%d, %d)\n", adjacent[i].x, adjacent[i].y);
    }

    free(adjacent);
    adjacent = NULL;

    return EXIT_SUCCESS;
}