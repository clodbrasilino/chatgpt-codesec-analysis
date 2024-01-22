#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char *list, size_t size_list) {
    if (tuple == NULL || string == NULL || list == NULL || size_list <= 0) {
        return;
    }

    size_t len_tuple = strnlen(tuple, size_list - 1);
    size_t len_string = strnlen(string, size_list - len_tuple - 1);

    if((len_tuple + len_string) < size_list) {
        memcpy(list, tuple, len_tuple);
        list[len_tuple] = '\0';
        memcpy(list + len_tuple, string, len_string);
        list[len_tuple + len_string] = '\0';
    } else {
        printf("Buffer not large enough to store concatenated string\n");
    }
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-";
    char list[MAX_SIZE] = "";

    tupleToList(tuple, string, list, sizeof(list));

    printf("%s\n", list);

    return 0;
}