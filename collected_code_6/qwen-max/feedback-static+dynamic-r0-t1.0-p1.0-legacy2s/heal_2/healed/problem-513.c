#include <stdio.h>
#include <stddef.h>

typedef struct {
    size_t capacity;
} List;

int main() {
    List myList = {0};
    printf("Capacity: %zu\n", myList.capacity);
    return 0;
}