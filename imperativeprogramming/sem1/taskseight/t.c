#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int similar(const char *s1, const char *s2)
{
    int n = strlen(s1);
    int m = strlen(s2);
    
    if (abs(n - m) > 1) return 0;
    
    int errors = 0;
    int i = 0, j = 0;
    
    while (i < n && j < m) {
        if (s1[i] != s2[j]) {
            errors++;
            if (errors > 1) return 0;
            
            if (n > m) i++;
            else if (m > n) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    
    if (i < n || j < m) errors++;
    
    return errors <= 1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char word[256];
    int c, len = 0;
    int last_was_puk = 0;

    while ((c = fgetc(stdin)) != EOF)
    {
        if (isalpha(c) || c == '_')
        {
            word[len++] = (char)c;
        }
        else
        {
            if (len > 0)
            {
                word[len] = '\0';
                
                if (similar(word, "puk"))
                {
                    if (!last_was_puk) {
                        printf("#include <stdio.h>\n");
                        printf("#include <stdlib.h>\n");
                        printf("#include <memory.h>\n");
                        printf("#include <ctype.h>\n");
                        printf("#include <math.h>\n");
                        printf("#include <string.h>\n");
                    }
                    last_was_puk = 1;
                }
                else if (similar(word, "hiya"))
                {
                    printf("__auto_type ");
                    last_was_puk = 0;
                }
                else if (similar(word, "yaz"))
                {
                    printf("freopen(\"input.txt\", \"r\", stdin);\n");
                    printf("    freopen(\"output.txt\", \"w\", stdout);");
                    last_was_puk = 0;
                }
                else if (strcmp(word, "r") == 0)
                {
                    printf("return");
                    last_was_puk = 0;
                }
                else
                {
                    printf("%s", word);
                    last_was_puk = 0;
                }
                
                len = 0;
            }

            if ((c != '\n' && c != '\r') || !last_was_puk) {
                putchar(c);
            }
            
            if (last_was_puk && c == '\n') {
                last_was_puk = 0;
            }
        }
    }

    if (len > 0)
    {
        word[len] = '\0';
        
        if (similar(word, "puk"))
        {
            printf("#include <stdio.h>\n");
            printf("#include <stdlib.h>\n");
            printf("#include <memory.h>\n");
            printf("#include <ctype.h>\n");
            printf("#include <math.h>\n");
            printf("#include <string.h>\n");
        }
        else if (similar(word, "hiya"))
        {
            printf("__auto_type");
        }
        else if (similar(word, "yaz"))
        {
            printf("freopen(\"input.txt\", \"r\", stdin);\n");
            printf("    freopen(\"output.txt\", \"w\", stdout);");
        }
        else if (strcmp(word, "r") == 0)
        {
            printf("return");
        }
        else
        {
            printf("%s", word);
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}