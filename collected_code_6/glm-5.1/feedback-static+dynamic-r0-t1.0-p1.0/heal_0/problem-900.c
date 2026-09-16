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

    size_t total_len = (size_t)num_len + strlen(str) + 1;
    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    int written = snprintf(result, total_len, "%d%s", number, str);
    if (written < 0 || (size_t)written >= total_len) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void) {
    const char *original = "_apples";
    char *new_str = prepend_number(42, original);
    
    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    }
    
    return 0;
}