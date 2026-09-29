#include <stdio.h>
#include <string.h>

int check_list(char **list, int size, char *str) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(list[i], str) != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char *list[] = {"hello", "hello", "hello"};
    char *str = "hello";
    int size = sizeof(list) / sizeof(list[0]);

    if (check_list(list, size, str)) {
        printf("All elements are equal to the given string\n");
    } else {
        printf("All elements are not equal to the given string\n");
    }
  
    return 0;
}