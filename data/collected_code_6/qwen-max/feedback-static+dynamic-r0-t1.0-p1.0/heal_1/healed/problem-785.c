#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *tuple_str_to_int(const char *str, size_t *len) {
    if (str == NULL || len == NULL) return NULL;
    char *copy = strdup(str);
    if (copy == NULL) return NULL;
    
    *len = 0;
    for (char *token = strtok(copy, ","); token; token = strtok(NULL, ",")) {
        (*len)++;
    }
    
    int *result = malloc((*len) * sizeof(int));
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    
    char *p = copy;
    for (size_t i = 0; i < *len; i++) {
        p = strtok(p ? NULL : copy, ",");
        result[i] = (int)strtol(p, NULL, 10);
    }
    
    free(copy);
    return result;
}

int main() {
    const char *str1 = "1,2,3";
    const char *str2 = "4,5,6";
    const char *str3 = "7,8,9";

    size_t len1 = 0, len2 = 0, len3 = 0;
    int *tuple1 = tuple_str_to_int(str1, &len1);
    int *tuple2 = tuple_str_to_int(str2, &len2);
    int *tuple3 = tuple_str_to_int(str3, &len3);

    if (tuple1 != NULL) {
        for (size_t i = 0; i < len1; i++) {
            printf("%d ", tuple1[i]);
        }
        free(tuple1);
    } else {
        fprintf(stderr, "Error: Unable to convert the string to integer tuple.\n");
    }

    if (tuple2 != NULL) {
        for (size_t i = 0; i < len2; i++) {
            printf("%d ", tuple2[i]);
        }
        free(tuple2);
    } else {
        fprintf(stderr, "Error: Unable to convert the string to integer tuple.\n");
    }

    if (tuple3 != NULL) {
        for (size_t i = 0; i < len3; i++) {
            printf("%d ", tuple3[i]);
        }
        free(tuple3);
    } else {
        fprintf(stderr, "Error: Unable to convert the string to integer tuple.\n");
    }

    return 0;
}