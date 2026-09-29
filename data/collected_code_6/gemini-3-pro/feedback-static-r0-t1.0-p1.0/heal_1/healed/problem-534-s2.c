#include <stdio.h>
#include <string.h>
#include <stddef.h>

const char* search_string(const char* haystack, const char* needle, ptrdiff_t* position) {
    if (haystack == NULL || needle == NULL || position == NULL) {
        return NULL;
    }

    const char* found = strstr(haystack, needle);

    if (found != NULL) {
        *position = found - haystack;
    } else {
        *position = -1;
    }

    return found;
}

int main(void) {
    const char* text = "The quick brown fox jumps over the lazy dog.";
    const char* pattern = "brown";
    ptrdiff_t pos = -1;

    const char* result = search_string(text, pattern, &pos);

    if (result != NULL) {
        printf("Pattern found at position: %td\n", pos);
    } else {
        printf("Pattern not found.\n");
    }

    return 0;
}