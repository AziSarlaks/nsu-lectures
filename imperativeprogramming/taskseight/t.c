#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int similar(const char *s1, const char *s2)
{
    int n = strlen(s1);
    int m = strlen(s2);
    int dp[n + 1][m + 1];

    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            int a = dp[i - 1][j] + 1;
            int b = dp[i][j - 1] + 1;
            int c = dp[i - 1][j - 1] + cost;
            int min = a < b ? a : b;
            if (c < min)
                min = c;
            dp[i][j] = min;
        }
    }

    return dp[n][m] <= 1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char word[256];
    int c, len = 0;
    int lwp = 0;

    while ((c = fgetc(stdin)) != EOF)
    {
        if (isalpha(c))
        {
            word[len++] = (char)c;
        }
        else
        {
            if (len > 0)
            {
                word[len] = '\0';
                len = 0;

                if (similar(word, "puk"))
                {
                    printf("#include <stdio.h>\n");
                    printf("#include <stdlib.h>\n");
                    printf("#include <memory.h>\n");
                    printf("#include <ctype.h>\n");
                    printf("#include <math.h>\n");
                    printf("#include <string.h>\n");
                    printf("\n");
                    lwp = 1;
                }
                else if (similar(word, "hiya"))
                {
                    printf("__auto_type");
                    lwp = 0;
                }
                else if (similar(word, "yaz"))
                {
                    printf("freopen(\"input.txt\", \"r\", stdin);\n");
                    printf("    freopen(\"output.txt\", \"w\", stdout);");
                    lwp = 0;
                }
                else if (strcmp(word, "r") == 0)
                {
                    printf("return");
                    lwp = 0;
                }
                else
                {
                    printf("%s", word);
                    lwp = 0;
                }
            }

            if (!(lwp && c == '\n'))
                putchar(c);
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
