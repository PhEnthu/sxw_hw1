#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    /*judge whether the two matrix legitimate*/
    if((a.cols != b.cols)||(a.rows != b.rows)){
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0,0);
    }
    else {
        int i,j;
        Matrix c = create_matrix(a.rows,a.cols);
        for(i = 0; i < a.cols; i++){
            for(j = 0; j < a.rows; j++){
                c.data[i][j] = a.data[i][j]+b.data[i][j];
            }
        }
        return c;
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo

    /*judge whether the two matrix legitimate*/
    if((a.cols != b.cols)||(a.rows != b.rows)){
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0,0);
    }
    else {
        int i,j;
        Matrix c = create_matrix(a.rows,a.cols);
        for(i = 0; i < a.cols; i++){
            for(j = 0; j < a.rows; j++){
                c.data[i][j] = a.data[i][j]-b.data[i][j];
            }
        }
        return c;
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo

     /*judge whether the two matrix legitimate*/
    if(a.cols != b.rows){
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0,0);       
    }
    else{
        int i,k,j;
        Matrix c = create_matrix(a.rows,b.cols);
        for(i = 0; i < a.rows; i++){
            for(j = 0; j < b.cols; j++){
                for(k = 0; k < a.cols; k++){
                    c.data[i][j] += a.data[i][k]*b.data[k][j];
                }
            }
        }
        return c;
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
    for(int i = 0;i < a.rows; i++){
        for(int j = 0; j < a.cols; j++){
            a.data[i][j] = a.data[i][j]*k;
        }
    }
    return a;
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    int i,j;
    Matrix b = create_matrix(a.cols,a.rows);
    for(i = 0; i <a.rows; i++){
        for(j = 0; j < a.cols; j++){
            b.data[j][i] = a.data[i][j];
        }
    }
    return b;
}

double det_matrix(Matrix a)
{
    // ToDo
    /*judge whether the  matrix is legitimate*/
    if(a.cols != a.rows){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }

    double s = 0;
    int i, j, n = a.cols; 
    /*judge the row of the matrix*/
    if(a.cols == 2){
        s = a.data[0][0]*a.data[1][1]-a.data[1][0]*a.data[0][1];
        return s;
    }
    else if(a.cols == 1){
        return a.data[0][0];
    }
    else if(a.cols == 0){
        return 0;
    }
    else{
        int p = 1;    //the varible of p is used as the function (-1)^n
        Matrix c = create_matrix(n-1,n-1);
        for(i = 0;i < n; i++){
            for(int k = 0; k  < n-1; k++){
                for(int m = 0; m < n-1; m++){
                    if(m < i){
                        c.data[k][m] = a.data[k+1][m];
                    }
                    else{
                        c.data[k][m] = a.data[k+1][m+1];
                    }
                }
            }
            s+=p*a.data[0][i]*det_matrix(c);
            p = -p;
        }
        return s;
    }
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    // ToDo
    return 0;
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