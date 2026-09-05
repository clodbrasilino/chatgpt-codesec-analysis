#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *prepend_number(int number, const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    int num_len = snprintf(NULL, 0, "%d", number);
    if (num_len < 0) {
        return NULL;
    }
    
    size_t total_len = (size_t)num_len + strlen(str);
    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    int written = snprintf(result, total_len + 1, "%d%s", number, str);
    if (written < 0 || (size_t)written != total_len) {
        free(result);
        return NULL;
    }
    
    return result;
}

int main(void) {
    const char *original = "apples";
    int number = 42;
    
    char *new_string = prepend_number(number, original);
    if (new_string == NULL) {
        return EXIT_FAILURE;
    }
    
    printf("%s\n", new_string);
    
    free(new_string);
    
    return EXIT_SUCCESS;
}