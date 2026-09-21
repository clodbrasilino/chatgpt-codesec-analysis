#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    
    size_t target_len = 4;
    size_t replacement_len = 3;
    
    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    size_t count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
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
    while ((tmp = strstr(current, target)) != NULL) {
        size_t len = tmp - current;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, current, len);
        dest += len;
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, replacement, replacement_len);
        dest += replacement_len;
        
        current = tmp + target_len;
    }
    
    size_t remaining_len = 0;
    while (current[remaining_len] != '\0') {
        remaining_len++;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, current, remaining_len);
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