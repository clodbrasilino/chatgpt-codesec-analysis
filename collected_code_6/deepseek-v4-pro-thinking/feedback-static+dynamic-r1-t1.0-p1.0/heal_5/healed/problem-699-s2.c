#include <stdio.h>
#include <string.h>

const char* minSwaps(const char *s, const char *t) {
    static char buffer[64];

    if (s == NULL || t == NULL) {
        return "Not Possible";
    }

    size_t n = strlen(s);
    if (n != strlen(t)) {
        return "Not Possible";
    }

    long long ones_s = 0;
    long long ones_t = 0;
    long long diff = 0;

    for (size_t i = 0; i < n; i++) {
        if ((s[i] != '0' && s[i] != '1') ||
            (t[i] != '0' && t[i] != '1')) {
            return "Not Possible";
        }
        if (s[i] == '1') {
            ones_s++;
            if (t[i] == '0') {
                diff++;
            }
        }
        if (t[i] == '1') {
            ones_t++;
        }
    }

    if (ones_s != ones_t) {
        return "Not Possible";
    }

    snprintf(buffer, sizeof(buffer), "%lld", diff);
    return buffer;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }

    printf("%s\n", minSwaps(argv[1], argv[2]));
    return 0;
}