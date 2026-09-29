#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrange(const char *s) {
    int count[26] = {0};
    size_t n = strlen(s);
    for (size_t i = 0; i < n; ++i) {
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

    return max_count <= (n + 1) / 2;
}

int main() {
    const char s[] = "aab";
    bool result = canRearrange(s);
    printf(result ? "Yes\n" : "No\n");
    return 0;
}