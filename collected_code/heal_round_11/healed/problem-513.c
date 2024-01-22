#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char **list, size_t *size_list) {
    if (tuple != NULL && string != NULL && list != NULL && size_list > 0) {
        size_t len_tuple = strnlen(tuple, MAX_SIZE - 1);
        size_t len_string = strnlen(string, MAX_SIZE - len_tuple - 1);
        if ((len_tuple + len_string + 1) <= *size_list) {
            *list = malloc(len_tuple + len_string + 1);
            if (*list) {
                memcpy(*list, tuple, len_tuple);
                (*list)[len_tuple] = '\0';
                strncat(*list, string, len_string);
            } else {
                printf("Failed to allocate memory\n");
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
        printf("%s\n", list);
        free(list);
        return 0;
    } else {
        printf("Failed to allocate memory\n");
        return -1;
    }
}
