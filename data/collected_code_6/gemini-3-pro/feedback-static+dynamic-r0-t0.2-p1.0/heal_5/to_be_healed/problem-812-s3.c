#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    const char* target = "road";
    const char* replacement = "rd.";
    
    size_t target_len = 4;
    size_t replacement_len = 3;

    size_t count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL && (size_t)(tmp - input) <= input_len - target_len) {
        count++;
        tmp += target_len;
    }

    size_t new_len = input_len - (count * target_len) + (count * replacement_len);
    char* result = (char*)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char* current = input;
    char* dest = result;
    size_t remaining_space = new_len + 1;

    while ((tmp = strstr(current, target)) != NULL && (size_t)(tmp - input) <= input_len - target_len) {
        size_t len = (size_t)(tmp - current);
        
        if (len >= remaining_space) {
            free(result);
            return NULL;
        }
        
        for (size_t i = 0; i < len; i++) {
            dest[i] = current[i];
        }
        dest += len;
        remaining_space -= len;
        
        if (replacement_len >= remaining_space) {
            free(result);
            return NULL;
        }
        
        for (size_t i = 0; i < replacement_len; i++) {
            dest[i] = replacement[i];
        }
        dest += replacement_len;
        remaining_space -= replacement_len;
        
        current = tmp + target_len;
    }
    
    size_t remaining_len = 0;
    while (current[remaining_len] != '\0' && (size_t)((current - input) + remaining_len) < input_len) {
        remaining_len++;
    }
    
    if (remaining_len >= remaining_space) {
        free(result);
        return NULL;
    }
    
    for (size_t i = 0; i < remaining_len; i++) {
        dest[i] = current[i];
    }
    dest[remaining_len] = '\0';

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