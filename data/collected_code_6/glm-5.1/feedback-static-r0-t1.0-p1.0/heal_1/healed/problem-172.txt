#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_std_occurrence(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int count = 0;
    const char *ptr = str;
    while ((ptr = strstr(ptr, "std")) != NULL) {
        count++;
        ptr++;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int count = find_std_occurrence(argv[1]);
    printf("%d\n", count);
    return EXIT_SUCCESS;
}