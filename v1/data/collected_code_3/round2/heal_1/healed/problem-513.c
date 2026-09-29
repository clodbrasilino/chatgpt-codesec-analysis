#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **convert_tuple_to_list(char *tuple[], int size, char *str) {
    char **list = malloc(sizeof(char *) * size * 2);
    if(list == NULL) {
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < size; i++) {
        list[j] = malloc(strlen(tuple[i]) + 1);
        if(list[j] == NULL) {
            for(--j; j >= 0; --j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        strcpy(list[j], tuple[i]);
        j++;
        list[j] = malloc(strlen(str) + 1);
        if(list[j] == NULL) {
            for(--j; j >= 0; --j) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        strcpy(list[j], str);
        j++;
    }
    return list;
}

int main() {
    char *tuple[] = {"apple", "banana", "cherry"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    char *str = "fruit";
    char **list = convert_tuple_to_list(tuple, size, str);
    if(list == NULL) {
        return 1;
    }
    for (int i = 0; i < size * 2; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
    }
    free(list);
    return 0;
}