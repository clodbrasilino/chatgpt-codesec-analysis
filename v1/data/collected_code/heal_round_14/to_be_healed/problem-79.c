#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word, size_t size) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (!word || size == 0 || strlen(word) >= size) return false;
    return (size - 1) % 2 != 0;
}

int main() {
    const char *word = "Hello";
    if (!word) return -1;
    
    /* Possible weaknesses found:
     *  'strnlen' specified bound 8 exceeds source size 6 [-Wstringop-overread]
     */
    size_t size = strnlen(word, sizeof(word)) + 1;
    bool result = isLengthOdd(word, size);
   
    return 0;
}