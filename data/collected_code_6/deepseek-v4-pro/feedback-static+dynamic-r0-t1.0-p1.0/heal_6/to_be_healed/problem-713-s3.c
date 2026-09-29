#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_NAME_LENGTH 63

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[64];
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
    
    size_t name_len = strnlen(tuple->name, sizeof(tuple->name));
    if (name_len == 0 || name_len >= sizeof(tuple->name)) {
        return false;
    }
    
    if (tuple->name[MAX_NAME_LENGTH] != '\0') {
        return false;
    }
    
    if (tuple->score < 0.0f || tuple->score > 100.0f) {
        return false;
    }
    
    if (!tuple->active) {
        return false;
    }
    
    return true;
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
    
    const Tuple *null_pointer = NULL;
    /* Possible weaknesses found:
     *  Condition 'is_valid_tuple(null_pointer)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_valid_tuple' returns 0
     *  Condition 'is_valid_tuple(null_pointer)' is always false
     */
    printf("NULL tuple: %s\n", is_valid_tuple(null_pointer) ? "Valid" : "Invalid");
    
    return 0;
}