#include <stdio.h>
#include <string.h>

static int is_reverse(const char *a, const char *b)
{
    size_t len;

    if (a == NULL || b == NULL)
        return 0;

    len = strlen(a);
    if (len != strlen(b))
        return 0;

    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[len - 1 - i])
            return 0;
    }

    return 1;
}

int count_reverse_pairs(char **strings, int n)
{
    int count = 0;

    if (strings == NULL || n <= 0)
        return 0;

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL)
            continue;

        for (int j = i + 1; j < n; j++) {
            if (strings[j] == NULL)
                continue;

            if (is_reverse(strings[i], strings[j]))
                count++;
        }
    }

    return count;
}

int main(void)
{
    char *strings[] = {
        "abc", "cba", "hello", "olleh", "abc", "aba", "aba"
    };
    int n = (int)(sizeof(strings) / sizeof(strings[0]));

    printf("%d\n", count_reverse_pairs(strings, n));

    return 0;
}