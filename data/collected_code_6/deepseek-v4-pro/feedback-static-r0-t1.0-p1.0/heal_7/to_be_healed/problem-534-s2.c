#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

int search_literal(const char *haystack, const char *needle, int *location) {
    if (haystack == NULL || needle == NULL || location == NULL) {
        return -1;
    }

    size_t needle_len = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'needle_len>=1024' is redundant or the array 'needle[4]' is accessed at index 1023, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (needle[needle_len] != '\0') {
        needle_len++;
        /* Possible weaknesses found:
         *  Assuming that condition 'needle_len>=1024' is not redundant
         */
        if (needle_len >= MAX_BUFFER_SIZE) {
            return -1;
        }
    }

    if (needle_len == 0) {
        *location = 0;
        return 0;
    }

    size_t haystack_len = 0;
    while (haystack[haystack_len] != '\0') {
        haystack_len++;
        if (haystack_len >= MAX_BUFFER_SIZE) {
            return -1;
        }
    }

    for (size_t i = 0; i < haystack_len; i++) {
        if (i + needle_len > haystack_len) {
            break;
        }
        
        size_t j = 0;
        while (j < needle_len && haystack[i + j] == needle[j]) {
            j++;
        }
        
        if (j == needle_len) {
            *location = (int)i;
            return 0;
        }
    }

    return -1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown";
    int position = -1;

    int result = search_literal(text, pattern, &position);

    if (result == 0) {
        printf("Pattern found at position %d\n", position);
    } else {
        printf("Pattern not found\n");
    }

    pattern = "fox";
    position = -1;
    result = search_literal(text, pattern, &position);

    if (result == 0) {
        printf("Pattern found at position %d\n", position);
    } else {
        printf("Pattern not found\n");
    }

    pattern = "cat";
    position = -1;
    result = search_literal(text, pattern, &position);

    if (result == 0) {
        printf("Pattern found at position %d\n", position);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}