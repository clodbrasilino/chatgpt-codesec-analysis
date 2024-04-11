#include <stdio.h>
#include <string.h>

int find_occurrences(char *str) {
    int count = 0;
    char *ptr = str;

    while((ptr = strstr(ptr, "std")) != NULL) {
        count++;
        ptr++;
    }

    return count;
}

int main() {
    char str[] = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    printf("Occurrences of 'std': %d\n", find_occurrences(str));
    return 0;
}