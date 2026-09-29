#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    size_t target_len = strlen(target);
    size_t replacement_len = strlen(replacement);
    size_t input_len = strlen(input);

    int count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
        count++;
        tmp += target_len;
    }

    if (count == 0) {
        char* result = malloc(input_len + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, input);
        return result;
    }

    size_t result_len = input_len - (count * target_len) + (count * replacement_len);
    char* result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    char* dest = result;
    const char* src = input;
    while ((tmp = strstr(src, target)) != NULL) {
        size_t len = tmp - src;
        memcpy(dest, src, len);
        dest += len;
        
        memcpy(dest, replacement, replacement_len);
        dest += replacement_len;
        
        src = tmp + target_len;
    }
    
    strcpy(dest, src);

    return result;
}

int main(void) {
    const char* original = "The long road ahead is a dangerous road.";
    char* abbreviated = abbreviate_road(original);

    if (abbreviated != NULL) {
        printf("Original: %s\n", original);
        printf("Abbreviated: %s\n", abbreviated);
        free(abbreviated);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}