#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define NAME_BUFFER_SIZE 64
#define MAX_SCORE 100.0f
#define MIN_SCORE 0.0f

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
    
    if (tuple->name[NAME_BUFFER_SIZE - 1] != '\0') {
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

bool update_tuple_name(Tuple *tuple, const char *new_name) {
    if (tuple == NULL || new_name == NULL) {
        return false;
    }
    
    size_t max_len = sizeof(tuple->name) - 1;
    size_t len = strnlen(new_name, max_len);
    
    if (len > max_len) {
        len = max_len;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->name, new_name, len);
    tuple->name[len] = '\0';
    
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
        test_cases[i].name[NAME_BUFFER_SIZE - 1] = '\0';
        
        size_t name_len = strnlen(test_cases[i].name, NAME_BUFFER_SIZE);
        if (name_len >= NAME_BUFFER_SIZE) {
            test_cases[i].name[NAME_BUFFER_SIZE - 1] = '\0';
        }
        
        printf("Tuple %zu: %s\n", i + 1, 
               is_valid_tuple(&test_cases[i]) ? "Valid" : "Invalid");
    }
    
    process_active_tuples(test_cases, test_count);
    
    return 0;
}