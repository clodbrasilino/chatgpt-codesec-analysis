#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    if (!word) return false;
    size_t length = strnlen(word, size);
    return length % 2 != 0;
}

int main() {
    const char* word = "Hello";
    if (!word) return -1;
    size_t size = strlen(word);
    bool result = isLengthOdd(word, size);
    return 0;
}