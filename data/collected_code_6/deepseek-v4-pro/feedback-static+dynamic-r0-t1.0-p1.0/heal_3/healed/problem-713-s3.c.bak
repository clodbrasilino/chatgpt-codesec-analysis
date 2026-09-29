#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int id;
    char name[32];
    float score;
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
    
    size_t name_length = strnlen(tuple->name, 32);
    if (name_length == 32) {
        return false;
    }
    
    if (tuple->score < 0.0f || tuple->score > 100.0f) {
        return false;
    }
    
    return true;
}

int main(void) {
    Tuple test_cases[] = {
        {1, "John Doe", 85.5f},
        {-1, "Jane Smith", 92.0f},
        {2, "", 75.0f},
        {3, "Bob", -10.0f},
        {4, "Alice", 105.0f},
        {5, "Valid Name", 50.0f}
    };
    
    size_t test_count = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < test_count; i++) {
        printf("Tuple %zu: %s\n", i + 1, 
               is_valid_tuple(&test_cases[i]) ? "Valid" : "Invalid");
    }
    
    const Tuple *null_tuple = NULL;
    
    if (null_tuple == NULL) {
        printf("NULL tuple: Invalid\n");
    } else {
        printf("NULL tuple: %s\n", 
               is_valid_tuple(null_tuple) ? "Valid" : "Invalid");
    }
    
    return 0;
}