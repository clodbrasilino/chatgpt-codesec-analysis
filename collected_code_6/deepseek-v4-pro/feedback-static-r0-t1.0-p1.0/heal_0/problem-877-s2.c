#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

void sort_string(char *str) {
    size_t len = strlen(str);
    qsort(str, len, sizeof(char), compare_chars);
}

int main(void) {
    char str[1024];
    
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    sort_string(str);
    
    printf("%s\n", str);
    
    return 0;
}