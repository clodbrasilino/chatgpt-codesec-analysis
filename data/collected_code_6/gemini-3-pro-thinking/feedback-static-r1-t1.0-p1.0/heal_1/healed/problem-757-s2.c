#include <stdio.h>
#include <stddef.h>

#define MAX_STR_LEN 4096

static size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

int is_reverse(const char *s1, const char *s2) {
    size_t len1;
    size_t len2;
    size_t i;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    len1 = safe_strlen(s1, MAX_STR_LEN);
    len2 = safe_strlen(s2, MAX_STR_LEN);

    if (len1 != len2 || len1 == MAX_STR_LEN) {
        return 0;
    }

    for (i = 0; i < len1; ++i) {
        if (s1[i] != s2[len1 - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

size_t count_reverse_pairs(const char **strs, size_t count) {
    size_t pairs = 0;
    size_t i;
    size_t j;

    if (strs == NULL || count == 0) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (strs[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < count; ++j) {
            if (strs[j] == NULL) {
                continue;
            }
            if (is_reverse(strs[i], strs[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void) {
    const char *string_list[] = {
        "hello",
        "olleh",
        "world",
        "dlrow",
        "test",
        "tset",
        "abc"
    };
    size_t list_size;
    size_t pairs_count;

    list_size = sizeof(string_list) / sizeof(string_list[0]);
    pairs_count = count_reverse_pairs(string_list, list_size);
    
    printf("%zu\n", pairs_count);

    return 0;
}