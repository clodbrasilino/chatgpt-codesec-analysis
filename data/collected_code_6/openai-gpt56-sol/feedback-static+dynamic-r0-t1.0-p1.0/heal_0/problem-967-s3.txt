#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool contains_all_vowels(const char *string)
{
    bool found[5] = {false, false, false, false, false};

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        switch (tolower((unsigned char)*string)) {
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
        ++string;
    }

    return found[0] && found[1] && found[2] && found[3] && found[4];
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    if (contains_all_vowels(input)) {
        puts("Accepted");
    } else {
        puts("Rejected");
    }

    if (ferror(stdout)) {
        return 1;
    }

    return 0;
}