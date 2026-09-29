#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* extract_between_quotes(const char* str) {
    const char* p = str;
    while (*p) {
        if (*p == '\"') {
            const char* start = ++p;
            while (*p && *p != '\"') {
                ++p;
            }
            if (*p) {
                char* result = malloc(p - start + 1);
                strncpy(result, start, p - start);
                result[p - start] = '\0';
                return result;
            }
        }
        ++p;
    }
    return NULL;
}

int main() {
    const char* str = "This is a \"test\" string.";
    char* result = extract_between_quotes(str);
    if (result) {
        printf("Extracted string: %s\n", result);
        free(result);
    } else {
        printf("No string found between quotes.\n");
    }
    return 0;
}