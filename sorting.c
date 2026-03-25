#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp = fopen("sorting_data.txt", "r");

    char buffer[256];
    char *line = NULL;
    size_t line_len = 0;

    while (fgets(buffer, sizeof(buffer), fp))
    {
        size_t chunk_len = strlen(buffer);
        char *tmp = realloc(line, line_len + chunk_len + 1);
        if (!tmp) {
            free(line);
            return 1;
        }
        line = tmp;

        // add part of line
        memcpy(line + line_len, buffer, chunk_len);
        line_len += chunk_len;
        line[line_len] = '\0';

        // if all okey
        if (buffer[chunk_len - 1] == '\n')
        {
            printf("%s", line);
            free(line);
            line = NULL;
            line_len = 0;
        }
    }

    free(line);
    fclose(fp);
}
