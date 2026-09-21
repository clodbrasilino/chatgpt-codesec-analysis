#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *flatten_tuple_list(const char *list[], int len) {
    if (len <= 0) return NULL;
    int total_len = 0;
    for (int i = 0; i < len; ++i) {
        size_t list_len = strlen(list[i]);
        total_len += list_len + 2;
    }
    --total_len;
    char *result = (char *)malloc(total_len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';
    for (int i = 0; i < len; ++i) {
        size_t list_len = strlen(list[i]);
        strncat(result, list[i], total_len - strlen(result));
        if (i < len - 1) {
            strncat(result, ", ", total_len - strlen(result));
        }
    }
    return result;
}

int main() {
    const char *tuple_list[] = {"one", "two", "three"};
    int len = 3;
    char *flat_string = flatten_tuple_list(tuple_list, len);
    if (flat_string != NULL) {
        printf("%s\n", flat_string);
        free(flat_string);
    } else {
        printf("Failed to create flat string\n");
    }
    return 0;
}