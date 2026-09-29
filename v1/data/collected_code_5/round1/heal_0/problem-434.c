#include <stdio.h>
#include <string.h>

int match(const char *str) {
    const char *s = str;
    if (*s != 'a') return 0;
    s++;

    while (*s != '\0') {
        if (*s != 'b') return 0;
        s++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    printf("Does the string follow the rules? %s\n", match(argv[1]) ? "Yes" : "No");
    return 0;
}