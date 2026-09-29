#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *flatten_tuple_list(const char *list[], int len) {
    if (len <= 0) return NULL;
    int total_len = 0;
    for (int i = 0; i < len; ++i) {
        total_len += strlen(list[i]) + 2; // 1 for ",", 1 for " "
    }
    --total_len; // Remove the last extra comma or space
    char *result = (char *)malloc(total_len + 1); // +1 for null terminator
    if (result == NULL) return NULL;
    result[0] = '\0';
    for (int i = 0; i < len; ++i) {
        size_t pos = strlen(result);
        strncat(result, list[i], total_len - pos);
        if (i < len - 1) {
            result[pos + strlen(list[i])] = ',';
            result[pos + strlen(list[i]) + 1] = ' ';
            result[pos + strlen(list[i]) + 2] = '\0';
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