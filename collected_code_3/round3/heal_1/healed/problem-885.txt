#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHARS 256

bool areIsomorphic(char* str1, char* str2)
{
    int m = strlen(str1);
    int n = strlen(str2);

    if (m != n)
      return false;

    int map[MAX_CHARS];
    memset(map, -1, sizeof(map));

    bool marked[MAX_CHARS] = {false};

    for (int i = 0; i < n; i++)
    {
        if (map[(unsigned char)str1[i]] == -1)
        {
            if (marked[(unsigned char)str2[i]] == true)
                return false;

            marked[(unsigned char)str2[i]] = true;

            map[(unsigned char)str1[i]] = str2[i];
        }

        else if (map[(unsigned char)str1[i]] != str2[i])
            return false;
    }

    return true;
}

int main()
{
   char str1[] = "aab";
   char str2[] = "xxy";
   printf("%s\n", areIsomorphic(str1, str2) ? "Yes" : "No");

   char str3[] = "aab";
   char str4[] = "xyz";
   printf("%s\n", areIsomorphic(str3, str4) ? "Yes" : "No");

   return 0;
}