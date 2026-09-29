#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    if (!word || size == 0 || strlen(word) >= size) return false;
    return (size - 1) % 2 != 0;
}

int main() {
    const char *word = "Hello";
    if (!word) return -1;
    
    size_t size = strnlen(word, sizeof(word)) + 1;
    bool result = isLengthOdd(word, size);
   
    return 0;
}