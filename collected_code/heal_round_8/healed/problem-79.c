#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    if (!word || size == 0 || word[size - 1] != '\0') return false;
    return size % 2 != 0;
}

int main() {
    const char *word = "Hello";

    if (!word) return -1;

    size_t size = strlen(word) + 1;
    bool result = isLengthOdd(word, size);

    return 0;
}