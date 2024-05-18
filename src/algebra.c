/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-05-18 16:49:56
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-05-18 23:52:52
 * @FilePath: \hw1\src\algebra.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: butterfalls 1731860884@qq.com
 * @Date: 2024-05-18 16:49:56
 * @LastEditors: butterfalls 1731860884@qq.com
 * @LastEditTime: 2024-05-18 22:59:06
 * @FilePath: \hw1\src\algebra.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "algebra.h"
#include <stdio.h>
#include <math.h>

int min(int x, int y) {
    return (x < y) ? x : y;
}

void swap_rows(Matrix m, int row1, int row2) {
    for (int i = 0; i < m.cols; i++) {
        double temp = m.data[row1][i];
        m.data[row1][i] = m.data[row2][i];
        m.data[row2][i] = temp;
    }
}

void copy_matrix(Matrix source, Matrix destination) {
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            destination.data[i][j] = source.data[i][j];
        }
    }
}

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    Matrix result;
    if (a.rows != b.rows || a.cols != b.cols) 
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0); 
    }

    result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) 
    {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    Matrix result;

    if (a.rows != b.rows || a.cols != b.cols) 
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }

    result=create_matrix(a.rows , a.cols);

    for (int i = 0; i<a.rows ;i++)
    {
        for (int j=0; j<a.cols; j++)
        {
            result.data[i][j]=a.data[i][j]-b.data[i][j];
        }
    }

    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }

    Matrix result;
    result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++)
            {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }

    return result;
}

Matrix transpose_matrix(Matrix a)
{
     Matrix result = create_matrix(a.cols, a.rows);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }

    return result;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0.0;
    }

    if (a.rows == 1) {
        return a.data[0][0];
    }

    double det = 0.0;
    int sign;
    Matrix submatrix;

    for (int j = 0; j < a.cols; j++) {
        submatrix = create_matrix(a.rows - 1, a.cols - 1);
        for (int i = 1; i < a.rows; i++) {
            for (int k = 0; k < a.cols; k++) {
                if (k < j) {
                    submatrix.data[i - 1][k] = a.data[i][k];
                } else if (k > j) {
                    submatrix.data[i - 1][k - 1] = a.data[i][k];
                }
            }
        }
        sign = (j % 2 == 0) ? 1 : -1;
        det += sign * a.data[0][j] * det_matrix(submatrix);
    }

    return det;
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }

    double det = det_matrix(a);
    if (det == 0.0) {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }

    Matrix inverse = create_matrix(a.rows, a.cols);
    Matrix adjugate = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            Matrix submatrix = create_matrix(a.rows - 1, a.cols - 1);
            for (int x = 0; x < a.rows; x++) {
                for (int y = 0; y < a.cols; y++) {
                    if (x < i && y < j) {
                        submatrix.data[x][y] = a.data[x][y];
                    } else if (x < i && y > j) {
                        submatrix.data[x][y - 1] = a.data[x][y];
                    } else if (x > i && y < j) {
                        submatrix.data[x - 1][y] = a.data[x][y];
                    } else if (x > i && y > j) {
                        submatrix.data[x - 1][y - 1] = a.data[x][y];
                    }
                }
            }
            adjugate.data[j][i] = ((i + j) % 2 == 0) ? det_matrix(submatrix) : -det_matrix(submatrix);
        }
    }

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            inverse.data[i][j] = adjugate.data[i][j] / det;
        }
    }

    return inverse;
}

int rank_matrix(Matrix a)
{
    int rank = min(a.rows, a.cols);
    Matrix b = create_matrix(a.rows, a.cols);
    copy_matrix(a, b);

    for (int i = 0; i < rank; i++) {
        if (b.data[i][i] == 0) {
            int found = 0;
            for (int k = i + 1; k < a.rows; k++) {
                if (b.data[k][i] != 0) {
                    swap_rows(b, i, k);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                rank--;
                continue;
            }
        }
        for (int j = i + 1; j < a.rows; j++) {
            double factor = b.data[j][i] / b.data[i][i];
            for (int k = i; k < a.cols; k++) {
                b.data[j][k] -= factor * b.data[i][k];
            }
        }
    }

    return rank;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0.0;
    }

    double trace = 0.0;
    for (int i=0; i < a.rows; i++)
    {
        trace += a.data[i][i];
    }

    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}