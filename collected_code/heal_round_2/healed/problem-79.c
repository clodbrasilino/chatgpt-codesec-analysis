#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    size_t length = strnlen(word, size);
    return length % 2 != 0;
}

int main() {
    const char* word = "Hello";
    size_t size = strlen(word) + 1;
    bool result = isLengthOdd(word, size);
    return 0;
}