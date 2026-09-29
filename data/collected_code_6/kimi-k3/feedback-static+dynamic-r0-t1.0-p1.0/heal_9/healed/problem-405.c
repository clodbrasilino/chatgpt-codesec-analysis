#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[64];
    double value;
} Tuple;

bool tuple_contains(const Tuple *tuple, const char *search_name) {
    if (tuple == NULL || search_name == NULL) {
        return false;
    }
    size_t search_len = strnlen(search_name, sizeof(tuple->name));
    if (search_len >= sizeof(tuple->name)) {
        return false;
    }
    size_t tuple_len = strnlen(tuple->name, sizeof(tuple->name));
    if (tuple_len != search_len) {
        return false;
    }
    return memcmp(tuple->name, search_name, tuple_len) == 0;
}

void tuple_init(Tuple *tuple, int id, const char *name, double value) {
    if (tuple == NULL) {
        return;
    }
    tuple->id = id;
    if (name != NULL) {
        size_t name_len = strnlen(name, sizeof(tuple->name) - 1);
        if (name_len < sizeof(tuple->name)) {
            size_t copy_len = (name_len < sizeof(tuple->name) - 1) ? name_len : sizeof(tuple->name) - 1;
            memcpy(tuple->name, name, copy_len);
            tuple->name[copy_len] = '\0';
        } else {
            tuple->name[0] = '\0';
        }
    } else {
        tuple->name[0] = '\0';
    }
    tuple->value = value;
}

int main(void) {
    Tuple my_tuple;
    tuple_init(&my_tuple, 1, "example", 42.5);
    const char *search = "example";
    
    if (tuple_contains(&my_tuple, search)) {
        printf("Element exists in tuple\n");
    } else {
        printf("Element not found in tuple\n");
    }
    
    return 0;
}