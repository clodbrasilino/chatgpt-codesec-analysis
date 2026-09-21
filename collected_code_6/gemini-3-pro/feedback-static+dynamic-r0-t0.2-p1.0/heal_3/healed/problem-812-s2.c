#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 8192

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    
    size_t target_len = sizeof("road") - 1;
    size_t replacement_len = sizeof("rd.") - 1;
    
    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len == MAX_INPUT_LEN && input[MAX_INPUT_LEN - 1] != '\0') {
        return NULL;
    }

    int count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
        if (tmp > input + input_len) break;
        count++;
        tmp += target_len;
    }

    size_t result_len = input_len + count * (replacement_len - target_len) + 1;
    char* result = (char*)malloc(result_len);
    if (result == NULL) {
        return NULL;
    }

    char* dest = result;
    const char* src = input;
    size_t remaining = result_len;

    while ((tmp = strstr(src, target)) != NULL && tmp < input + input_len) {
        size_t prefix_len = tmp - src;
        
        int written = snprintf(dest, remaining, "%.*s", (int)prefix_len, src);
        if (written < 0 || (size_t)written >= remaining) break;
        dest += written;
        remaining -= written;

        written = snprintf(dest, remaining, "%s", replacement);
        if (written < 0 || (size_t)written >= remaining) break;
        dest += written;
        remaining -= written;
        
        src = tmp + target_len;
    }
    
    snprintf(dest, remaining, "%s", src);

    return result;
}

int main(void) {
    const char* original = "The long road leads to another road.";
    char* abbreviated = abbreviate_road(original);

    if (abbreviated != NULL) {
        printf("Original: %s\n", original);
        printf("Abbreviated: %s\n", abbreviated);
        free(abbreviated);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}