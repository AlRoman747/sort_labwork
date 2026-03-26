#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp = fopen("sorting_data.txt", "r");

    int v = 15;
    char buffer[256];
    char *line = NULL;
    int line_len = 0;

    int *arr = malloc(sizeof(int) * v);
    if (!arr) return 1;
    int len_arr = 0;


    while (fgets(buffer, sizeof(buffer), fp)) {
        int chunk_len = strlen(buffer);
        char *tmp = realloc(line, line_len + chunk_len + 1);
        if (!tmp) {
            free(line);
            return 1;
        }
        line = tmp;

        // add part of line
        memcpy(line + line_len, buffer, chunk_len);
        line_len += chunk_len; // increase line len
        line[line_len] = '\0';

        arr[len_arr++] = buffer[0];

        if (len_arr == v) {
            v *= 2;
            arr = realloc(arr, sizeof(int) * v);
            if (!arr) return 1;
        }

        // if len line in buffer size
        /*
        if (buffer[chunk_len - 1] == '\n')
        {
            printf("%s", line);
            free(line);
            line = NULL;
            line_len = 0;
        }

    printf("\n");
    */
    }
    for (int i=0; i < len_arr; i++) {
        printf("%c ", arr[i]);
    }



    free(line);
    fclose(fp);
    return 0;
}
