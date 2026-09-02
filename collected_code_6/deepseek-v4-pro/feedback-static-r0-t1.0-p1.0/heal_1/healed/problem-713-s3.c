#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int id;
    char name[32];
    float score;
    bool active;
} Tuple;

bool is_valid_tuple(const Tuple *tuple) {
    if (tuple == NULL) {
        return false;
    }
    
    if (tuple->id < 0) {
        return false;
    }
    
    if (tuple->name[0] == '\0') {
        return false;
    }
    
    size_t name_length = strnlen(tuple->name, sizeof(tuple->name));
    if (name_length >= sizeof(tuple->name)) {
        return false;
    }
    
    if (tuple->score < 0.0f || tuple->score > 100.0f) {
        return false;
    }
    
    return true;
}

void print_validation_result(const char *label, const Tuple *tuple) {
    if (tuple != NULL) {
        printf("%s: %s\n", label, is_valid_tuple(tuple) ? "Valid" : "Invalid");
    } else {
        printf("%s: Invalid\n", label);
    }
}

int main(void) {
    Tuple test_cases[] = {
        {1, "John Doe", 85.5f, true},
        {-1, "Jane Smith", 92.0f, true},
        {2, "", 75.0f, false},
        {3, "Bob", -10.0f, true},
        {4, "Alice", 105.0f, false},
        {5, "Valid Name", 50.0f, true}
    };
    
    size_t test_count = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < test_count; i++) {
        printf("Tuple %zu: %s\n", i + 1, 
               is_valid_tuple(&test_cases[i]) ? "Valid" : "Invalid");
    }
    
    print_validation_result("NULL tuple", NULL);
    
    return 0;
}