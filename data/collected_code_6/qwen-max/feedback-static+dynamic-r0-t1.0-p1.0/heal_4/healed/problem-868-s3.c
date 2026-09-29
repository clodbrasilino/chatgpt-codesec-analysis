#include <stdio.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int len = 0;
    int lastWordLen = 0;
    int i = 0;

    while (s[i] != '\0') {
        if (isspace((unsigned char)s[i])) {
            if (len > 0) {
                lastWordLen = len;
                len = 0;
            }
        } else {
            len++;
        }
        i++;
    }

    return len > 0 ? len : lastWordLen;
}

int main() {
    const char *testCases[] = {"Hello, World!", "   fly me   to   the moon  ", "luffy is still joyboy", " "};
    const int expectedResults[] = {5, 4, 6, 0};
    const int numTestCases = 4;

    for (int j = 0; j < numTestCases; j++) {
        int result = lengthOfLastWord(testCases[j]);
        printf("Length of last word in \"%s\": %d (expected: %d)\n", testCases[j], result, expectedResults[j]);
    }

    return 0;
}