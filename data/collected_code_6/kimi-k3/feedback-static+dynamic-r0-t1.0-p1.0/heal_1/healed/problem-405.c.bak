#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[32];
} Tuple;

bool tuple_contains(const Tuple *tuple, const char *search_name) {
    if (tuple == NULL || search_name == NULL) {
        return false;
    }
    return strcmp(tuple->name, search_name) == 0;
}

int main(void) {
    Tuple my_tuple = {"example"};
    const char *search = "example";
    
    if (tuple_contains(&my_tuple, search)) {
        printf("Element exists in tuple\n");
    } else {
        printf("Element not found in tuple\n");
    }
    
    return 0;
}