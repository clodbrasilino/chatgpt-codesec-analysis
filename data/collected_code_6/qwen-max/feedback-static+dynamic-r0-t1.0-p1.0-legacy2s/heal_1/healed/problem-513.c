#include <stdio.h>
#include <stddef.h>

typedef struct {
    char **elements;
    size_t size;
    size_t capacity;
} List;

int main() {
    List myList = {NULL, 0, 0};
    // Example usage: Print the capacity of myList
    printf("Capacity: %zu\n", myList.capacity);
    return 0;
}