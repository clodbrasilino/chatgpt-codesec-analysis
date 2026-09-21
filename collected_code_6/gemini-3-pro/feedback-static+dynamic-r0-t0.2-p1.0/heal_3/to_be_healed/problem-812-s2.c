#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t target_len = strlen(target);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t replacement_len = strlen(replacement);
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    int count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
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

    while ((tmp = strstr(src, target)) != NULL) {
        size_t prefix_len = tmp - src;
        
        snprintf(dest, remaining, "%.*s", (int)prefix_len, src);
        dest += prefix_len;
        remaining -= prefix_len;

        snprintf(dest, remaining, "%s", replacement);
        dest += replacement_len;
        remaining -= replacement_len;
        
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