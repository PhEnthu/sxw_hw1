#include "algebra.h"
#include <stdio.h>
#include <math.h>

double mypow(double x, int n){
    double s = 1;
    for(int i = 0; i < n; i++){
        s *= x;
    }
    return s;
}

void exchange(double p[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int i, int i1, int rows, int cols){
    int j;
    double s = 0;
    for(j = 0; j < cols; j++){
        s = p[i][j];
        p[i][j] = p[i1][j];
        p[i1][j] = s;
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

    /*judge whether the inv_matrx is exist*/
    if(a.rows != a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0,0);
    }
    else if(det_matrix(a) == 0){
        printf("Error: The matrix is singular.\n");
        return create_matrix(0,0);
    }
    else{
        int n = a.cols, i, j;
        Matrix A = create_matrix(n,n), c = create_matrix(n-1,n-1);
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){

                /*-------        create Cofactors        --------*/
                for(int k = 0; k  < n-1; k++){
                    for(int m = 0; m < n-1; m++){
                        if(k < i){
                            if(m < j){
                                c.data[k][m] = a.data[k][m];
                            }
                            else{
                                c.data[k][m] = a.data[k][m+1];
                            }
                        }
                        else{
                            if(m < j){
                                c.data[k][m] = a.data[k+1][m];
                            }
                            else{
                                c.data[k][m] = a.data[k+1][m+1];
                            }
                        }
                    }
                }
                double det_c = det_matrix(c);
                A.data[j][i] = det_matrix(c)*mypow(-1,i+j);
                if(A.data[j][i] == 0) //去除浮点数的-0.00格式
                    A.data[j][i] = 0;
            }
        }
        double det = det_matrix(a);
        return scale_matrix(A,1.0/det);
    }    
}

int rank_matrix(Matrix a)
{
    // ToDo
    int r = a.rows;
    int i, j, i1 = -1, m = 0;
    
    i = 0;
    for(j = 0; j < a.cols; j++){
        i1 = -1;
        for(;i < a.rows;){
            if(a.data[i][j] != 0){
                for(m = i+1; m < a.rows; m++){
                    if(m != i)
                        for(int n = a.cols-1; n >= 0; n--){
                            a.data[m][n] += -(a.data[i][n]*a.data[m][j])/a.data[i][j];
                        }
                }
                i++;
            }
            else{
                /*向下查找是否在第j列有非零项（第i1项），若没有，i1值为-1*/
                for(m = i+1; m < a.rows; m++){
                    if((a.data[m][j] != 0)&&(i1<0)){
                        i1 = m;
                    }
                }
                if(i1 >= 0){
                    exchange(a.data, i, i1,a.rows,a.cols);
                    continue;
                }
                else;
            }
            break;
        }
    }

    
    for(i = 0; i < a.rows; i++){
        int counts = 0;

        for(int l = 0; l < a.cols; l++){
            if(a.data[i][l] != 0){
                counts++;
            }
        }
        if(counts == 0)
            r--;
    }
    return r;
}

double trace_matrix(Matrix a)
{
    // ToDo
    if(a.cols != a.rows){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else{
        double s = 0;
        int n = a.rows;

        for(int i = 0; i < n; i++){
            s += a.data[i][i];
        }
        return s;
    }
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