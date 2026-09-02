#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    float temperature;
    char status;
} Tuple;

bool is_valid_tuple(const Tuple *tuple) {
    if (tuple == NULL) {
        return false;
    }

    if (tuple->id < 0) {
        return false;
    }

    if (tuple->temperature < -273.15f || tuple->temperature > 1000.0f) {
        return false;
    }

    if (tuple->status != 'A' && tuple->status != 'I' && tuple->status != 'P') {
        return false;
    }

    return true;
}

int main(void) {
    Tuple valid_tuple = {1, 25.5f, 'A'};
    Tuple invalid_id = {-1, 25.5f, 'A'};
    Tuple invalid_temp = {1, -300.0f, 'A'};
    Tuple invalid_status = {1, 25.5f, 'X'};

    printf("Valid tuple: %s\n", is_valid_tuple(&valid_tuple) ? "true" : "false");
    printf("Invalid ID: %s\n", is_valid_tuple(&invalid_id) ? "true" : "false");
    printf("Invalid temperature: %s\n", is_valid_tuple(&invalid_temp) ? "true" : "false");
    printf("Invalid status: %s\n", is_valid_tuple(&invalid_status) ? "true" : "false");
    printf("NULL tuple: %s\n", is_valid_tuple(NULL) ? "true" : "false");

    return 0;
}