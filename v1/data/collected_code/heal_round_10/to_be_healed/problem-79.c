#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    if (!word || size == 0) return false;
    if (strnlen(word, size) < size - 1) return false; 
    return size % 2 != 0;
}

int main() {
    const char *word = "Hello";

    if (!word) return -1;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t size = strlen(word) + 1;
    bool result = isLengthOdd(word, size);

    return 0;
}