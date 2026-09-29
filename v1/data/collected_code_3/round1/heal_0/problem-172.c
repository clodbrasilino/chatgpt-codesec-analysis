#include <stdio.h>
#include <string.h>

int findOccurrences(char *str) {
    int count = 0;
    char *temp = str;
    while((temp = strstr(temp, "std")) != NULL) {
        count++;
        temp++;
    }
    return count;
}

int main() {
    char str[] = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    printf("Occurrences of 'std': %d\n", findOccurrences(str));
    return 0;
}