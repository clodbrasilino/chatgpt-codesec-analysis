#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

int get_adjacent_coordinates(Coordinate coord, Coordinate **adj_coords) {
    *adj_coords = malloc(8 * sizeof(Coordinate));
    if (*adj_coords == NULL) {
        return -1;
    }

    (*adj_coords)[0] = (Coordinate){coord.x - 1, coord.y};
    (*adj_coords)[1] = (Coordinate){coord.x + 1, coord.y};
    (*adj_coords)[2] = (Coordinate){coord.x, coord.y - 1};
    (*adj_coords)[3] = (Coordinate){coord.x, coord.y + 1};
    (*adj_coords)[4] = (Coordinate){coord.x - 1, coord.y - 1};
    (*adj_coords)[5] = (Coordinate){coord.x - 1, coord.y + 1};
    (*adj_coords)[6] = (Coordinate){coord.x + 1, coord.y - 1};
    (*adj_coords)[7] = (Coordinate){coord.x + 1, coord.y + 1};

    return 8;
}

int main() {
    Coordinate input_coord = {5, 5};
    Coordinate *adj_coords;
    int count = get_adjacent_coordinates(input_coord, &adj_coords);

    if (count == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        printf("(%d, %d)\n", adj_coords[i].x, adj_coords[i].y);
    }

    free(adj_coords);
    return 0;
}