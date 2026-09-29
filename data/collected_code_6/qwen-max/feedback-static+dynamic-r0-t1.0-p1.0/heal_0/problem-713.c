#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_TUPLE_SIZE 100

bool is_valid_value(int32_t value) {
    return (value >= 0 && value <= 100);
}

bool are_all_values_valid(const int32_t *tuple, size_t tuple_size) {
    if (tuple == NULL || tuple_size > MAX_TUPLE_SIZE) {
        return false;
    }
    for (size_t i = 0; i < tuple_size; ++i) {
        if (!is_valid_value(tuple[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    int32_t tuple[] = {50, 75, 90};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    bool result = are_all_values_valid(tuple, tuple_size);
    if (result) {
        return 0;
    } else {
        return 1;
    }
}