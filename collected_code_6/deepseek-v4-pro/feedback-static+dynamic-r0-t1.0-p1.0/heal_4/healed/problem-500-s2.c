#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(char **list, int count) {
    size_t total_length = 0;
    size_t len;
    int i;
    char *result;
    char *position;

    if (list == NULL || count <= 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (list[i] != NULL) {
            len = strnlen(list[i], SIZE_MAX);
            if (len > SIZE_MAX - total_length) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (total_length >= SIZE_MAX) {
        return NULL;
    }

    result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    position = result;
    for (i = 0; i < count; i++) {
        if (list[i] != NULL) {
            len = strnlen(list[i], SIZE_MAX);
            if (len > (size_t)((result + total_length) - position)) {
                free(result);
                return NULL;
            }
            if (position + len <= result + total_length) {
                memcpy(position, list[i], len);
                position += len;
            } else {
                free(result);
                return NULL;
            }
        }
    }

    *position = '\0';
    return result;
}

int main(void) {
    char *list1[] = {"Hello", " ", "World", "!"};
    char *list2[] = {"The", " ", "quick", " ", "brown", " ", "fox"};
    char *list3[] = {"", "Empty", "", "String", ""};
    char *result;

    result = concatenate_list(list1, 4);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = concatenate_list(list2, 7);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = concatenate_list(list3, 5);
    if (result != NULL) {
        printf("[%s]\n", result);
        free(result);
    }

    result = concatenate_list(NULL, 3);
    if (result == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}