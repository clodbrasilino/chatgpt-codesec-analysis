#include <stdio.h>
#include <string.h>

void minimizeString(char *str) {
    int len = strlen(str);
    int freq[26] = {0};

    for (int i = 0; i < len; i++) {
        freq[str[i] - 'a']++;
    }

    int minOccur = len;
    char minChar = 'a';

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 1 && freq[i] < minOccur) {
            minOccur = freq[i];
            minChar = i + 'a';
        }
    }

    for (int i = 0; i < len; i++) {
        if (str[i] == minChar) {
            for (int j = i; j < len - 1; j++) {
                str[j] = str[j+1];
            }
            len--;
            break;
        }
    }

    str[len] = '\0';
}

int main() {
    char str[] = "mississippi";
    minimizeString(str);
    printf("%s\n", str);
    return 0;
}