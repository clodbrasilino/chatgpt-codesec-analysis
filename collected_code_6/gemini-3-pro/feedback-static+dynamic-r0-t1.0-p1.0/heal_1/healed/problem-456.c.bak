#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (!str) {
        return;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t i = 0;
    size_t j = len - 1;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void reverse_string_list(char **list, size_t count) {
    if (!list) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i]) {
            reverse_string(list[i]);
        }
    }
}

int main(void) {
    size_t count = 3;
    char **list = malloc(count * sizeof(char *));
    if (!list) {
        return 1;
    }

    list[0] = strdup("Hello");
    list[1] = strdup("World");
    list[2] = strdup("C Programming");

    for (size_t i = 0; i < count; i++) {
        if (!list[i]) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
    }

    reverse_string_list(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}