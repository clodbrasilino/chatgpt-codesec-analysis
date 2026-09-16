#include <stdio.h>
#include <string.h>

void print_words(const char *str) {
    int first = 1;
    const char *p = str;
    putchar('[');
    while (*p) {
        while (*p == ' ' || *p == '\t') ++p;
        if (!*p) break;
        const char *start = p;
        while (*p && *p != ' ' && *p != '\t') ++p;
        if (!first) fputs(", ", stdout);
        putchar('\'');
        fwrite(start, 1, (size_t)(p - start), stdout);
        putchar('\'');
        first = 0;
    }
    putchar(']');
}

int main(int argc, char **argv) {
    if (argc == 2) {
        print_words(argv[1]);
        putchar('\n');
    } else if (argc > 2) {
        putchar('[');
        for (int i = 1; i < argc; ++i) {
            if (i > 1) fputs(", ", stdout);
            putchar('\'');
            fputs(argv[i], stdout);
            putchar('\'');
        }
        putchar(']');
        putchar('\n');
    } else {
        char line[4096];
        while (fgets(line, sizeof(line), stdin)) {
            line[strcspn(line, "\n")] = '\0';
            if (line[0] == '\0') continue;
            print_words(line);
            putchar('\n');
        }
    }
    return 0;
}