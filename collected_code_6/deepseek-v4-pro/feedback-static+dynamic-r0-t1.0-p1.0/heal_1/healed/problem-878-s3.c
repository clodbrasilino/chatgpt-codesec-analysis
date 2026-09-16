#include <stdbool.h>
#include <stddef.h>

bool tuple_has_k_elements(const void *tuple, size_t elem_size, size_t tuple_size, size_t k) {
    if (tuple == NULL || elem_size == 0) {
        return false;
    }
    return tuple_size / elem_size == k;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4};
    size_t elem_size = sizeof(int);
    size_t tuple_size = sizeof(tuple);
    size_t k = 4;

    bool result = tuple_has_k_elements(tuple, elem_size, tuple_size, k);
    
    return result ? 0 : 1;
}