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

static void print_validation_result(const char *label, bool result) {
    printf("%s: %s\n", label, result ? "true" : "false");
}

int main(void) {
    Tuple valid_tuple = {1, 25.5f, 'A'};
    Tuple invalid_id = {-1, 25.5f, 'A'};
    Tuple invalid_temp = {1, -300.0f, 'A'};
    Tuple invalid_status = {1, 25.5f, 'X'};

    print_validation_result("Valid tuple", is_valid_tuple(&valid_tuple));
    print_validation_result("Invalid ID", is_valid_tuple(&invalid_id));
    print_validation_result("Invalid temperature", is_valid_tuple(&invalid_temp));
    print_validation_result("Invalid status", is_valid_tuple(&invalid_status));
    print_validation_result("NULL tuple", is_valid_tuple(NULL));

    return 0;
}