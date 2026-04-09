#include <iostream>
#include <windows.h>

int **init_matrix(int rows, int cols);
void output(int **matrix, int rows, int cols);
int input(int **matrix, int rows, int cols);
int **sort(int **matrix, int rows, int cols, int key);

int main() {
    // SetConsoleCP(CP_UTF8);
    // SetConsoleOutputCP(CP_UTF8);
    printf("Введите размерность матрицы (M x N): ");
    int M, N;
    if (scanf("%d %d", &M, &N) != 2 || N < 1 || M < 1) {
        printf("Некорректный ввод.");
        return 1;
    }
    M += 1;
    int **matrix = init_matrix(M, N);
    if (matrix == NULL) {
        return 1;
    }
    for (int j = 0; j < N; j++) {
        matrix[0][j] = j + 1;
    }

    //input
    printf("Введите значения матрицы: ");
    if (input(matrix, M, N)) {
        return 1;
    }
    output(matrix, M, N);

    printf("Выберите столбец, по которому следует отсортировать значения:");
    int K;
    if (scanf("%d", &K) != 1 || K < 1 || K > N) {
        printf("Некорректный ввод");
        return 1;
    }
    int **result = sort(matrix, M, N, K - 1);
    output(result, M, N);
    return 0;
}   

int **init_matrix(int rows, int cols) {
    int **matrix;
    try {
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
    } catch (std::bad_alloc e) {
        printf("Не получилось выделить память.");
        return NULL;
    }

    return matrix;
}

void output(int **matrix, int rows, int cols) {
    printf("Текущая матрица:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("%d\n", matrix[i][cols - 1]);
    }
}

int input(int **matrix, int rows, int cols) {
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Некорректный ввод");
                return 1;
            }
        }
    }
    return 0;
}

int **sort(int **matrix, int rows, int cols, int key) {
    int **sort_row = init_matrix(rows - 1, 2);
    if (sort_row == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows - 1; i++) {
        sort_row[i][0] = matrix[i + 1][key];
        sort_row[i][1] = i + 1;
    }
    

    //bubble sort
    for (int i = 0; i < rows - 2; i++) {
        for (int j = i + 1; j < rows - 1; j++) {
            if (sort_row[j][0] < sort_row[i][0]) {
                int temp_v = sort_row[i][0];
                int temp_i = sort_row[i][1];

                sort_row[i][0] = sort_row[j][0];
                sort_row[i][1] = sort_row[j][1];

                sort_row[j][0] = temp_v;
                sort_row[j][1] = temp_i;
            }
        }
    }

    //restore 
    int **result = init_matrix(rows, cols);
    //numbers row
    for (int j = 0; j < cols; j++) {
        result[0][j] = j + 1;
    }
    //restore rows
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            result[i + 1][j] = matrix[sort_row[i][1]][j];
        }
    }
    return result;
}