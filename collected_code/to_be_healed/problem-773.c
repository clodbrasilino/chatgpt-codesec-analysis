#include <stdio.h>
#include <string.h>

void findSubstrings(const char* str, const char* substr) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int lenStr = strlen(str);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int lenSub = strlen(substr);
    int count = 0;

    for (int i = 0; i <= lenStr - lenSub; i++) {
        int j;

        for (j = 0; j < lenSub; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
        }

        if (j == lenSub) {
            printf("Substring found at position %d\n", i + 1);
            count++;
        }
    }

    printf("Substring \"%s\" occurs %d times in the string.\n", substr, count);
}

int main() {
    const char* str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    const char* substr = "ipsum";

    findSubstrings(str, substr);

    return 0;
}