#include <stdio.h>
#include <string.h>

void minimizeString(char *str) {
    if (!str || !*str) return;

    int freq[26] = {0};
    char *ptr = str;

    while (*ptr != '\0') {
        if(*ptr >= 'a' && *ptr <= 'z'){
            freq[*ptr - 'a']++;
        }
        ptr++;
    }

    int minOccur = ptr - str;
    char minChar = 'a';

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 1 && freq[i] < minOccur) {
            minOccur = freq[i];
            minChar = i + 'a';
        }
    }

    ptr = str;
    char *dst = str;
    while (*ptr != '\0') {
        if (*ptr != minChar) {
            *dst = *ptr;
            dst++;
        }
        ptr++;
    }

    *dst = '\0';
}

int main() {
    char str[] = "mississippi";
    minimizeString(str);
    printf("%s\n", str);
    return 0;
}