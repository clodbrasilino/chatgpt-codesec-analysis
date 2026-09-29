#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str) {
    int i, j = 0, len;
    len = strlen(str);
    char temp[len + 1];

    for(i = 0; i < len; i++) {
        if(!isdigit(str[i])) {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';

    strcpy(str, temp);
}

void remove_digits_from_list(char **list, int size) {
    for(int i = 0; i < size; i++) {
        remove_digits(list[i]);
    }
}

int main() {
    char list[][20] = {"Hello123", "World456", "789Test"};
    int size = sizeof(list) / sizeof(list[0]);
   
    char *list_ptr[size];
    for(int i = 0; i < size; i++) {
        list_ptr[i] = list[i];
    }

    remove_digits_from_list(list_ptr, size);

    for(int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}