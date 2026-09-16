#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool contains_substring(const char *strings[], size_t count, const char *substring) {
    if (strings == NULL || substring == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strstr(strings[i], substring) != NULL) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    const char *values[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(values) / sizeof(values[0]);
    const char *target = "ban";
    
    if (contains_substring(values, count, target)) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }
    
    return 0;
}