#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define MIN_PASSWORD_LENGTH 8

bool is_valid_password(const char *password)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length;
    size_t i;

    if (password == NULL)
    {
        return false;
    }

    length = strlen(password);

    if (length < MIN_PASSWORD_LENGTH)
    {
        return false;
    }

    for (i = 0; i < length; i++)
    {
        unsigned char ch = (unsigned char)password[i];

        if (isupper(ch))
        {
            has_upper = true;
        }
        else if (islower(ch))
        {
            has_lower = true;
        }
        else if (isdigit(ch))
        {
            has_digit = true;
        }
        else if (ispunct(ch))
        {
            has_special = true;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void)
{
    const char *passwords[] = {
        "Valid1!Password",
        "Short1!",
        "NoSpecial1",
        "alllowercase1!",
        NULL
    };
    size_t i;

    for (i = 0; i < sizeof(passwords) / sizeof(passwords[0]); i++)
    {
        printf("%s\n", is_valid_password(passwords[i]) ? "true" : "false");
    }

    return 0;
}