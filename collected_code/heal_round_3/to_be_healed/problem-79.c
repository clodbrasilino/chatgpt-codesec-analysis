#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    size_t length = strnlen(word, size);
    return length % 2 != 0;
}

int main() {
    const char* word = "Hello";
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t size = strlen(word) + 1;
    bool result = isLengthOdd(word, size);
    return 0;
}