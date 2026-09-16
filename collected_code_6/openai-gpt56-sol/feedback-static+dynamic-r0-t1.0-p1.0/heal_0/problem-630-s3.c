#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

int get_adjacent_coordinates(Coordinate coordinate,
                             Coordinate **adjacent,
                             size_t *count)
{
    static const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    if (adjacent == NULL || count == NULL) {
        return -1;
    }

    *adjacent = NULL;
    *count = 0;

    Coordinate *result = malloc(8 * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < 8; ++i) {
        result[i].x = coordinate.x + offsets[i][0];
        result[i].y = coordinate.y + offsets[i][1];
    }

    *adjacent = result;
    *count = 8;
    return 0;
}

int main(void)
{
    Coordinate coordinate;
    Coordinate *adjacent = NULL;
    size_t count = 0;

    if (scanf("%d %d", &coordinate.x, &coordinate.y) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (get_adjacent_coordinates(coordinate, &adjacent, &count) != 0) {
        fputs("Failed to extract adjacent coordinates\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)\n", adjacent[i].x, adjacent[i].y) < 0) {
            free(adjacent);
            return EXIT_FAILURE;
        }
    }

    free(adjacent);
    return EXIT_SUCCESS;
}