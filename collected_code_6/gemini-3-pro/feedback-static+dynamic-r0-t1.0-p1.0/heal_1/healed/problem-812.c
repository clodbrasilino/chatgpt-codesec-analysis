#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    
    size_t target_len = 0;
    while (target[target_len] != '\0') target_len++;
    
    size_t replacement_len = 0;
    while (replacement[replacement_len] != '\0') replacement_len++;
    
    size_t input_len = 0;
    while (input[input_len] != '\0') input_len++;

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
        
        size_t i;
        for (i = 0; i <= input_len; i++) {
            result[i] = input[i];
        }
        return result;
    }

    size_t result_len = input_len - (count * target_len) + (count * replacement_len);
    char* result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    char* dest = result;
    const char* src = input;
    size_t remaining_size = result_len + 1;

    while ((tmp = strstr(src, target)) != NULL) {
        size_t len = (size_t)(tmp - src);
        
        if (len > remaining_size - 1) {
            len = remaining_size - 1;
        }
        
        size_t i;
        for (i = 0; i < len; i++) {
            dest[i] = src[i];
        }
        dest += len;
        remaining_size -= len;
        
        size_t copy_repl = replacement_len;
        if (copy_repl > remaining_size - 1) {
            copy_repl = remaining_size - 1;
        }
        for (i = 0; i < copy_repl; i++) {
            dest[i] = replacement[i];
        }
        dest += copy_repl;
        remaining_size -= copy_repl;
        
        src = tmp + target_len;
    }
    
    while (*src != '\0' && remaining_size > 1) {
        *dest++ = *src++;
        remaining_size--;
    }
    *dest = '\0';

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