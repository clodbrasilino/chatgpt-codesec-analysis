#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool contains_all_vowels(const char *str)
{
    bool found[5] = {false, false, false, false, false};

    if (str == NULL) {
        return false;
    }

    for (; *str != '\0'; ++str) {
        switch (tolower((unsigned char)*str)) {
            case 'a':
                found[0] = true;
                break;
            case 'e':
                found[1] = true;
                break;
            case 'i':
                found[2] = true;
                break;
            case 'o':
                found[3] = true;
                break;
            case 'u':
                found[4] = true;
                break;
            default:
                break;
        }
    }

    return found[0] && found[1] && found[2] && found[3] && found[4];
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return 1;
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (contains_all_vowels(input)) {
        puts("Accepted");
    } else {
        puts("Rejected");
    }

    return 0;
}