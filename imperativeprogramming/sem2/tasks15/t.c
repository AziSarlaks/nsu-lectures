#include <stdio.h>
#include <string.h>

int main()
{
    char line[105];
    fgets(line, sizeof(line), stdin);

    int len = strlen(line);
    int i = 0;

    while (i < len)
    {
        while (i < len && line[i] == ' ')
            i++;

        if (i >= len || line[i] == '\n')
            break;

        fprintf(stdout, "[");

        if (line[i] == '"')
        {
            i++;
            while (i < len && line[i] != '"')
            {
                fputc(line[i], stdout);
                i++;
            }
            i++;
        }
        else
        {
            while (i < len && line[i] != ' ' && line[i] != '\n')
            {
                fputc(line[i], stdout);
                i++;
            }
        }

        fprintf(stdout, "]\n");
    }
    return 0;
}