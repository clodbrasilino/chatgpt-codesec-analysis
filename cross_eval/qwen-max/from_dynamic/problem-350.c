#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* minimize_string(char *str) {
    int counts[256] = {0};
    int max_count = 0, to_remove = '\0';
    for (int i = 0; str[i] != '\0'; i++) {
        counts[(unsigned char)str[i]]++;
        if (counts[(unsigned char)str[i]] > max_count) {
            max_count = counts[(unsigned char)str[i]];
            to_remove = str[i];
        }
    }

    int src = 0, dst = 0;
    while (str[src] != '\0') {
        if (str[src] != to_remove) {
            str[dst++] = str[src];
        }
        src++;
    }
    str[dst] = '\0';

    return str;
}

int main() {
    char str[] = "example string with characters";
    printf("Original: %s\n", str);
    char *result = minimize_string(str);
    printf("Minimized: %s\n", result);
    return 0;
}