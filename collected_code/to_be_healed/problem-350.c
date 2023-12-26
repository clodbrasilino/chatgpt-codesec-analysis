#include <stdio.h>
#include <string.h>

void minimizeString(char *str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
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