#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int binary_search(char* arr, int key, int left, int right) {

    while (left < right) {
        int mid = (left + right) / 2;
        if (key < arr[mid]){
            left++;
        } else { right = mid; }
    }

    return left;

}

void binary_insert_sort(char* arr, int len_arr) {

    for (int i=1; i < len_arr; i++) {
        char key = arr[i];
        int pos = binary_search(arr, key, 0, i);
        int j = i;
        while (j > pos) {
            arr[j] = arr[--j];
        }
        arr[pos] = key;

    }
}


int main()
{

    FILE *fp = fopen("sorting_data.txt", "r");

        int v = 15;
        char buffer[256];
        char *line = NULL;
        int line_len = 0;
        char **lines = NULL;
        int count = 0;
        int capacity = 0;

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

            // добавляем кусок строки
            memcpy(line + line_len, buffer, chunk_len);
            line_len += chunk_len;
            line[line_len] = '\0';

            // если строка закончилась
            if (chunk_len > 0 && buffer[chunk_len - 1] == '\n') {

                if (count == capacity) {
                    capacity = capacity == 0 ? 4 : capacity * 2;
                    char **tmp_lines = realloc(lines, capacity * sizeof(char *));
                    if (!tmp_lines) {
                        free(line);
                        return 1;
                    }
                    lines = tmp_lines;
                }

                lines[count++] = line;

                line = NULL;
                line_len = 0;
            }
            arr[len_arr++] = buffer[0];

            if (len_arr == v) {
                v *= 2;
                arr = realloc(arr, sizeof(int) * v);
                if (!arr) return 1;
            }
    }
    if (line) {
        if (count == capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            char **tmp_lines = realloc(lines, capacity * sizeof(char *));
            if (!tmp_lines) {
                free(line);
                return 1;
            }
            lines = tmp_lines;
        }

        lines[count++] = line;
    }

    for (int i=0; i < count; i++) {
        printf("%c ", arr[i]);
    }

    printf("\n");

    binary_insert_sort(arr, len_arr);

    for (int i=0; i < count; i++) {
        printf("%c ", arr[i]);
    }




    free(lines);
    free(line);
    fclose(fp);
    return 0;
}
