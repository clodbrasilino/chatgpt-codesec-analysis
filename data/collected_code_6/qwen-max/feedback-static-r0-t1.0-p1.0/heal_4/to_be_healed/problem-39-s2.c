#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrange(const char *s, size_t len) {
    int count[26] = {0};
    for (size_t i = 0; i < len; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            count[s[i] - 'a']++;
        }
    }

    int max_count = 0;
    for (int i = 0; i < 26; ++i) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    return max_count <= (len + 1) / 2;
}

int main() {
    const char s[] = "aab";
    bool result = canRearrange(s, sizeof(s) - 1);
    /* Possible weaknesses found:
     * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    printf(result ? "Yes\n" : "No\n");
    return 0;
}