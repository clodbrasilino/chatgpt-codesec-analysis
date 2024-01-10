#include <stdio.h>
#include <string.h>

void minimizeString(char *str) {
    if (!str) return;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    if(len == 0) return;
    int freq[26] = {0};

    for (int i = 0; i < len; i++) {
        if(str[i] >= 'a' && str[i] <= 'z'){
            freq[str[i] - 'a']++;
        }
    }

    int minOccur = len;
    char minChar = 'a';

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 1 && freq[i] < minOccur) {
            minOccur = freq[i];
            minChar = i + 'a';
        }
    }

    int newlen = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != minChar) {
            str[newlen++] = str[i];
        }
    }

    str[newlen] = '\0';
}

int main() {
    char str[] = "mississippi";
    minimizeString(str);
    printf("%s\n", str);
    return 0;
}