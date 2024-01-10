#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(word);
    return length % 2 != 0;
}

int main() {
    char* word = "Hello";
    bool result = isLengthOdd(word);
    return 0;
}