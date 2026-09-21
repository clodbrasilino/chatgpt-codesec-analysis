#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_NAME_LENGTH 63
#define SCORE_MIN 0.0f
#define SCORE_MAX 100.0f

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH + 1];
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
    
    if (tuple->name[MAX_NAME_LENGTH] != '\0') {
        return false;
    }
    
    size_t name_len = strnlen(tuple->name, MAX_NAME_LENGTH);
    
    if (name_len == 0 || name_len > MAX_NAME_LENGTH) {
        return false;
    }
    
    if (tuple->score < SCORE_MIN || tuple->score > SCORE_MAX) {
        return false;
    }
    
    if (!tuple->active) {
        return false;
    }
    
    return true;
}

void safe_name_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int main(void) {
    Tuple tuple1;
    tuple1.id = 1;
    safe_name_copy(tuple1.name, "John Doe", sizeof(tuple1.name));
    tuple1.score = 85.5f;
    tuple1.active = true;
    
    Tuple tuple2;
    tuple2.id = -1;
    safe_name_copy(tuple2.name, "Jane Smith", sizeof(tuple2.name));
    tuple2.score = 92.0f;
    tuple2.active = true;
    
    Tuple tuple3;
    tuple3.id = 2;
    safe_name_copy(tuple3.name, "", sizeof(tuple3.name));
    tuple3.score = 75.0f;
    tuple3.active = false;
    
    Tuple tuple4;
    tuple4.id = 3;
    safe_name_copy(tuple4.name, "Bob", sizeof(tuple4.name));
    tuple4.score = -10.0f;
    tuple4.active = true;
    
    Tuple tuple5;
    tuple5.id = 4;
    safe_name_copy(tuple5.name, "Alice", sizeof(tuple5.name));
    tuple5.score = 105.0f;
    tuple5.active = false;
    
    Tuple tuple6;
    tuple6.id = 5;
    safe_name_copy(tuple6.name, "Valid Name", sizeof(tuple6.name));
    tuple6.score = 50.0f;
    tuple6.active = true;
    
    Tuple test_cases[] = {tuple1, tuple2, tuple3, tuple4, tuple5, tuple6};
    size_t test_count = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < test_count; i++) {
        printf("Tuple %zu: %s\n", i + 1, 
               is_valid_tuple(&test_cases[i]) ? "Valid" : "Invalid");
    }
    
    const Tuple *null_pointer = NULL;
    if (null_pointer == NULL) {
        printf("NULL tuple: Invalid\n");
    } else {
        printf("NULL tuple: %s\n", is_valid_tuple(null_pointer) ? "Valid" : "Invalid");
    }
    
    return 0;
}