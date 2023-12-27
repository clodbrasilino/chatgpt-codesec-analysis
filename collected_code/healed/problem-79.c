#include <stdbool.h>
#include <string.h>

bool isLengthOdd(const char* word) {
    size_t length = strlen(word);
    return length % 2 != 0;
}

int main() {
    char* word = "Hello";
    bool result = isLengthOdd(word);
    return 0;
}