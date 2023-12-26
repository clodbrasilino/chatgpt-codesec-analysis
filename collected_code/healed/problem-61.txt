#include <stdio.h>

int countSubstrings(const char str[])
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int sum = 0;
        for (int j = i; str[j] != '\0'; j++)
        {
            sum += str[j] - '0';
            if (sum == (j - i + 1))
            {
                count++;
            }
        }
    }
    return count;
}

int main()
{
    char str[] = "12345";
    int result = countSubstrings(str);
    printf("Number of substrings with the sum of digits equal to their length: %d\n", result);

    return 0;
}
