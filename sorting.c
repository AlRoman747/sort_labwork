#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int binary_search(char* arr, int key, int left, int right) {
    while (left < right) {
        int mid = (left + right) / 2;
        if (key < arr[mid]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int* binary_insert_sort(char* arr, int len_arr) {
    int *res = malloc(sizeof(int) * len_arr);
    for (int i = 0; i < len_arr; i++) {
        res[i] = i;
    }
    for (int i=1; i < len_arr; i++) {
        char key = arr[i];
        int key_idx = res[i];
        int pos = binary_search(arr, key, 0, i);
        for (int j = i; j > pos; j--) {
            arr[j] = arr[j - 1];
            res[j] = res[j - 1];
        }
        arr[pos] = key;
        res[pos] = key_idx;
    }
    return res;
}


int main()
{

    FILE *fp = fopen("revers_sorting_data.txt", "r");

        int v = 15;
        char buffer[256];
        char *line = NULL;
        int line_len = 0;
        char **lines = NULL;
        int count = 0;
        int capacity = 0;

        char *arr = malloc(sizeof(char) * v);
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

            memcpy(line + line_len, buffer, chunk_len);
            line_len += chunk_len;
            line[line_len] = '\0';

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
                arr = realloc(arr, sizeof(char) * v);
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

    for (int i=0; i < len_arr; i++) {
        printf("%c ", arr[i]);
    }

    printf("\n");

    int* res = binary_insert_sort(arr, len_arr);

    for (int i=0; i < len_arr; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
    for (int i=0; i<len_arr;i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
    for (int i=0; i<len_arr;i++){
        printf("%s\n", lines[res[i]]);
    }


    free(lines);
    free(line);
    fclose(fp);
    return 0;
}
