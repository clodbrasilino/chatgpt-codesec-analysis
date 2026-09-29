#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define NAME_BUFFER_SIZE 64
#define MAX_SCORE 100.0f
#define MIN_SCORE 0.0f

typedef struct {
    int id;
    char name[NAME_BUFFER_SIZE];
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
    
    size_t name_len = strnlen(tuple->name, NAME_BUFFER_SIZE);
    if (name_len >= NAME_BUFFER_SIZE) {
        return false;
    }
    
    if (tuple->score < MIN_SCORE || tuple->score > MAX_SCORE) {
        return false;
    }
    
    return true;
}

void process_active_tuples(const Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (tuples[i].active) {
            printf("Processing active tuple: %d\n", tuples[i].id);
        }
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
    
    const Tuple *null_tuple = NULL;
    printf("NULL tuple: %s\n", 
           is_valid_tuple(null_tuple) ? "Valid" : "Invalid");
    
    process_active_tuples(test_cases, test_count);
    
    return 0;
}