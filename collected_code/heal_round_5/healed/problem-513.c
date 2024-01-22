#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

void tupleToList(const char *tuple, const char *string, char *list, size_t size_list) {
    if (tuple == NULL || string == NULL || list == NULL || size_list <= 0) {
        return;
    }

    strncat(list, tuple, size_list-1);
    strncat(list, string, size_list - strlen(tuple) - 1);
}

int main() {
    const char tuple[] = "12345"; 
    const char string[] = "-"; 
    char list[MAX_SIZE] = "";

    tupleToList(tuple, string, list, sizeof(list)/sizeof(char));

    printf("%s\n", list);

    return 0;
}