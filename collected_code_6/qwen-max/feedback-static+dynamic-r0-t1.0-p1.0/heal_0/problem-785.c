#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *tuple_str_to_int(const char *str, size_t *len) {
    if (str == NULL || len == NULL) return NULL;
    char *copy = strdup(str);
    if (copy == NULL) return NULL;
    
    int *result = NULL;
    *len = 0;
    
    for (char *token = strtok(copy, ","); token; token = strtok(NULL, ",")) {
        (*len)++;
    }
    
    result = malloc((*len) * sizeof(int));
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    
    char *p;
    for (size_t i = 0, j = 0; i < *len; i++) {
        if (j == 0) p = strtok(copy, ",");
        else p = strtok(NULL, ",");
        result[i] = (int)strtol(p, NULL, 10);
        j++;
    }
    
    free(copy);
    return result;
}

int main() {
    const char *str = "1,2,3,4,5";
    size_t len = 0;
    int *tuple = tuple_str_to_int(str, &len);
    
    if (tuple != NULL) {
        for (size_t i = 0; i < len; i++) {
            printf("%d ", tuple[i]);
        }
        free(tuple);
    } else {
        fprintf(stderr, "Error: Unable to convert the string to integer tuple.\n");
    }
    
    return 0;
}