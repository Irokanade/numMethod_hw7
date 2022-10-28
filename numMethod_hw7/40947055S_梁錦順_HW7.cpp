//
//  main.cpp
//  numMethod_hw7
//
//  Created by Michael Leong on 21/10/2022.
//

#include <iostream>
#include <stdio.h>

using namespace std;

//code from hw3
#define MAX_N 100

//hardcode size for now
int gaussion(double matrixA[4][4], double vectorB[4], double result[4], int size) {
    
    //double matrixA[MAX_N][MAX_N];
    //double vectorB[MAX_N];
    //double result[MAX_N] = {1};
    double matrixL[MAX_N][MAX_N] = {0};
    
    int n = size;
    
    //init matrixL
    for(int i = 1; i <= n; i++) {
        matrixL[i][i] = 1;
    }
    
    //set matrixA
    /*for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= (n); j++) {
            scanf("%lf", &matrixA[i][j]);
        }
        scanf("%lf", &vectorB[i]);
    }*/
    
    //print result
    /*cout << "input matrix\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= (n); j++) {
            printf("%lf ", matrixA[i][j]);
        }
        printf("| %lf\n", vectorB[i]);
        //puts("");
    }
    printf("\n");*/
    
    //gaussion elimination
    for(int j = 1; j <= n-1; j++) {
        for(int i = 1; i <= n; i++) {
            if(i > j) {
                double coeff = matrixA[i][j]/matrixA[j][j];
                //printf("coeff: %lf\n", coeff);
                //printf("j: %d, i: %i\n", j, i);
                matrixL[i][j] = coeff;
                for(int k = 1; k <= n; k++) {
                    matrixA[i][k] = matrixA[i][k]-(coeff*matrixA[j][k]);
                }
                vectorB[i] = vectorB[i]-(coeff*vectorB[j]);
            }
        }
    }
    
    /*printf("matrixU\n");
    //print result
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= (n); j++) {
            printf("%lf ", matrixA[i][j]);
        }
        printf("| %lf\n", vectorB[i]);
        //puts("");
    }
    printf("\n");*/
    
    //backwards substitution
    for(int i = n; i >= 1; i--) {
        for(int j = i+1; j <= n; j++) {
            vectorB[i] = vectorB[i] - matrixA[i][j]*result[j];
        }
        result[i] = vectorB[i]/matrixA[i][i];
    }
    
    /*printf("result\n");
    //print result
    for(int i = 1; i <= n; i++) {
        printf("%lf ", result[i]);
    }
    puts("");
    
    printf("matrixL\n");
    //print matrixL
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= (n); j++) {
            printf("%lf ", matrixL[i][j]);
        }
        puts("");
    }
    printf("\n");*/
    
    
    
    return 0;
}
//end

//hw 7 stuffs
double f(double x, double y, double h, double k, double r) {
    return ((x-h)*(x-h))+((y-k)*(y-k))-(r*r);
}

double dfdh(double x, double y, double h) {
    return -2*(x-h);
}

double dfdk(double x, double y, double k) {
    return -2*(y-k);
}

double dfdr(double x, double y, double r) {
    return -2*r;
}

int multiNewton(double x1, double y1, double x2, double y2, double x3, double y3) {
    //std::ios::sync_with_stdio(false);
    //cin.tie(NULL);
    
    //3x3 matrix
    double DfMat[4][4];
    
    //initial vector
    double initVec[4] = {1, 1, 1, 1};
    
    //vector of 3 elements
    double FVec[4];
    
    //vector to store the result
    double result[4];
    
    //set DfMat matrix
    //row 1 f1
    DfMat[1][1] = dfdh(x1, y1, initVec[1]);
    DfMat[1][2] = dfdk(x1, y1, initVec[2]);
    DfMat[1][3] = dfdr(x1, y1, initVec[3]);
    //row 2 f2
    DfMat[2][1] = dfdh(x2, y2, initVec[1]);
    DfMat[2][2] = dfdk(x2, y2, initVec[2]);
    DfMat[2][3] = dfdr(x2, y2, initVec[3]);
    //row 1 f1
    DfMat[3][1] = dfdh(x3, y3, initVec[1]);
    DfMat[3][2] = dfdk(x3, y3, initVec[2]);
    DfMat[3][3] = dfdr(x3, y3, initVec[3]);
    
    //set FMat vector
    //row 1 f1
    FVec[1] = f(x1, y1, initVec[1], initVec[2], initVec[3])*-1;
    //row 2 f2
    FVec[2] = f(x2, y2, initVec[1], initVec[2], initVec[3])*-1;
    //row 3 f3
    FVec[3] = f(x3, y3, initVec[1], initVec[2], initVec[3])*-1;
    
    int count = 0;
    while(count < 100) {
        gaussion(DfMat, FVec, result, 3);
        //print result
        /*cout << "result\n";
        for(int i = 0; i <= 3; i++) {
            cout << result[i] << '\n';
        }*/
        
        //set initVec as result
        for(int i = 0; i <= 3; i++) {
            initVec[i] = result[i]+initVec[i];
        }
        
        //set DfMat matrix
        //row 1 f1
        DfMat[1][1] = dfdh(x1, y1, initVec[1]);
        DfMat[1][2] = dfdk(x1, y1, initVec[2]);
        DfMat[1][3] = dfdr(x1, y1, initVec[3]);
        //row 2 f2
        DfMat[2][1] = dfdh(x2, y2, initVec[1]);
        DfMat[2][2] = dfdk(x2, y2, initVec[2]);
        DfMat[2][3] = dfdr(x2, y2, initVec[3]);
        //row 1 f1
        DfMat[3][1] = dfdh(x3, y3, initVec[1]);
        DfMat[3][2] = dfdk(x3, y3, initVec[2]);
        DfMat[3][3] = dfdr(x3, y3, initVec[3]);
        
        //set FMat vector
        //row 1 f1
        FVec[1] = f(x1, y1, initVec[1], initVec[2], initVec[3])*-1;
        //row 2 f2
        FVec[2] = f(x2, y2, initVec[1], initVec[2], initVec[3])*-1;
        //row 3 f3
        FVec[3] = f(x3, y3, initVec[1], initVec[2], initVec[3])*-1;
        
        
        count++;
        
        /*cout << "initVec\n";
        cout << "h: " << initVec[1] << '\n';
        cout << "k: " << initVec[2] << '\n';
        cout << "r: " << initVec[3] << '\n';*/
    }
    
    //print result
    //cout << "test1\n";
    /*for(int i = 1; i <= 3; i++) {
        cout << initVec[i] << '\n';
    }*/
    
    cout << "h: " << initVec[1] << '\n';
    cout << "k: " << initVec[2] << '\n';
    cout << "r: " << initVec[3] << '\n';
    
    return 0;
}

int main(int argc, char *argv[]) {
    //test 1
    cout << "test1\n";
    multiNewton(-8, -4, 6, 9, 4, -9);
    
    cout << "test2\n";
    multiNewton(-1, 6, -2, -6, 5, 0);
    
    return 0;
}
