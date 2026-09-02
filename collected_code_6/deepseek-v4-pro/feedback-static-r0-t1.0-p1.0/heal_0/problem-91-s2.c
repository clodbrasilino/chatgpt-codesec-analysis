#include <stdio.h>
#include <string.h>

int substring_in_list(const char *substring, const char *list[], size_t list_size) {
    if (substring == NULL || list == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL && strstr(list[i], substring) != NULL) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    const char *strings[] = {
        "hello world",
        "foo bar",
        "test string",
        "example"
    };
    
    size_t list_size = sizeof(strings) / sizeof(strings[0]);
    
    if (substring_in_list("world", strings, list_size)) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }
    
    if (substring_in_list("xyz", strings, list_size)) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }
    
    return 0;
}