#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return *(char*)b - *(char*)a;
}

void findLargestNum(char* str) {
    qsort(str, strlen(str), sizeof(char), compare);
}

int main() {
    char str[] = "1234567890";
    findLargestNum(str);
    printf("Largest Number: %s\n", str);
    return 0;
}