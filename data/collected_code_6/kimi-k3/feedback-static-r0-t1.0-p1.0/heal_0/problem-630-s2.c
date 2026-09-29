#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate *coords;
    size_t count;
    size_t capacity;
} CoordinateList;

int init_coordinate_list(CoordinateList *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    
    list->coords = (Coordinate *)malloc(initial_capacity * sizeof(Coordinate));
    if (list->coords == NULL) {
        return -1;
    }
    
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

void free_coordinate_list(CoordinateList *list) {
    if (list != NULL && list->coords != NULL) {
        free(list->coords);
        list->coords = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int add_coordinate(CoordinateList *list, int x, int y) {
    if (list == NULL) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Coordinate *new_coords = (Coordinate *)realloc(list->coords, new_capacity * sizeof(Coordinate));
        if (new_coords == NULL) {
            return -1;
        }
        list->coords = new_coords;
        list->capacity = new_capacity;
    }
    
    list->coords[list->count].x = x;
    list->coords[list->count].y = y;
    list->count++;
    return 0;
}

int extract_adjacent_coordinates(int x, int y, CoordinateList *adjacent) {
    if (adjacent == NULL) {
        return -1;
    }
    
    if (init_coordinate_list(adjacent, 8) != 0) {
        return -1;
    }
    
    int offsets[8][2] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    };
    
    for (int i = 0; i < 8; i++) {
        int new_x = x + offsets[i][0];
        int new_y = y + offsets[i][1];
        
        if (add_coordinate(adjacent, new_x, new_y) != 0) {
            free_coordinate_list(adjacent);
            return -1;
        }
    }
    
    return 0;
}

void print_coordinates(const CoordinateList *list) {
    if (list == NULL || list->coords == NULL) {
        return;
    }
    
    for (size_t i = 0; i < list->count; i++) {
        printf("(%d, %d)\n", list->coords[i].x, list->coords[i].y);
    }
}

int main(void) {
    int x = 5;
    int y = 10;
    CoordinateList adjacent = {NULL, 0, 0};
    
    printf("Adjacent coordinates of (%d, %d):\n", x, y);
    
    if (extract_adjacent_coordinates(x, y, &adjacent) == 0) {
        print_coordinates(&adjacent);
        free_coordinate_list(&adjacent);
    } else {
        fprintf(stderr, "Failed to extract adjacent coordinates\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}