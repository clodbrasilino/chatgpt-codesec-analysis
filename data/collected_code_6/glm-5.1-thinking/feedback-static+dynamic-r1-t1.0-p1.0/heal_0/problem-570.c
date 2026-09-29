#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *s) {
    if (!s) {
        return NULL;
    }
    size_t len = strlen(s);
    char *d = malloc(len + 1);
    if (!d) {
        return NULL;
    }
    memcpy(d, s, len + 1);
    return d;
}

size_t remove_strings_containing(char **strings, size_t count, const char *needle) {
    if (!strings || !needle) {
        return 0;
    }
    size_t write_idx = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] && strstr(strings[i], needle)) {
            free(strings[i]);
        } else {
            strings[write_idx++] = strings[i];
        }
    }
    for (size_t i = write_idx; i < count; i++) {
        strings[i] = NULL;
    }
    return write_idx;
}

int main(void) {
    char *words[] = {
        duplicate_string("apple"),
        duplicate_string("banana"),
        duplicate_string("cherry"),
        duplicate_string("date"),
        duplicate_string("elderberry"),
        duplicate_string("fig")
    };
    
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *target = "an";
    
    size_t new_count = remove_strings_containing(words, count, target);
    
    for (size_t i = 0; i < new_count; i++) {
        if (words[i]) {
            printf("%s\n", words[i]);
        }
    }
    
    for (size_t i = 0; i < new_count; i++) {
        free(words[i]);
    }
    
    return 0;
}