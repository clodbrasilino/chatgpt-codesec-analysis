#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char **list, size_t *size_list) {
    if (tuple != NULL && string != NULL && list != NULL && *size_list > 0) {
        size_t len_tuple = strnlen(tuple, MAX_SIZE - 1);
        size_t len_string = strnlen(string, MAX_SIZE - len_tuple - 1);
        if (*size_list >= (len_tuple + len_string + 1)) {
            char *temp = realloc(*list, len_tuple + len_string + 1);
            if (temp) {
                *list = temp;
                strncpy(*list, tuple, len_tuple);
                (*list)[len_tuple] = '\0';
                strncat(*list, string, len_string);
            } else {
                printf("Failed to allocate memory\n");
                free(*list);
                *list = NULL;
            }
        } else {
            printf("Buffer not large enough to store concatenated string\n");
        }
    }
}

int main() {
    const char tuple[] = "12345";
    const char string[] = "-";
    size_t size_list = strlen(tuple) + strlen(string) + 1;
    char *list = malloc(size_list);

    if (list) {
        tupleToList(tuple, string, &list, &size_list);
        if (list) {
            printf("%s\n", list);
            free(list);
            list = NULL;
        }
        return 0;
    } else {
        printf("Failed to allocate memory\n");
        return -1;
    }
}