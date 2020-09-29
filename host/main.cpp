//@Author Dominic Gastaldo
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstdint>
#include "../libraries/Eigen/Dense"
#include "../libraries/Eigen/StdVector"


using Eigen::Matrix; 
using namespace Eigen;
typedef Matrix<float, Dynamic, Dynamic> Gradient; // Gradient
typedef Matrix<float, Dynamic, Dynamic> Laplacian; // Laplacian
typedef Matrix<float, Dynamic, Dynamic> spacial_vector; // Laplacian
typedef Matrix<float, Dynamic, Dynamic, Dynamic> threeDGrid; // Grid
typedef Matrix<float, Dynamic, Dynamic> twoDGrid; // Grid


//function prototypes
Gradient gradient(float x, float y);
float laplacian(float x, float y);
float source(float x, float y);


static float h=0.001;


/*

float source(float x, float y){
    
    return sinh(x);
}


float x_laplacian(float (*func)(spacial_vector r, float h), spacial_vector r, 2DGrid grid, float h){
    //2D Numerical Laplacian
    
    return h*func(r(0) + r(1)) - grid(x-h, y) - grid(x, y+h) - grid(x, y-h) + 4*grid(x, y);
}

float y_laplacian(float (*func)(float x, float y, float h), float x, float y, float h){
    //2D Numerical Laplacian
    
    return h*sinh(func(x,y)) - grid(x+h,y) - grid(x-h, y) - grid(x, y-h) + 4*grid(x,y);
}

**/




Laplacian construct_laplacian_matrix(int n){
    //Finite difference operator
    //Row for each equation nxm equations
    
    Laplacian lp_matrix = Laplacian::Zero(n*n, n*n);
    std::cout << "LP:\n" << lp_matrix << std::endl;
    
    
    //define solution grid 
    //define boundary grid
    //grid = solution grid U boundary grid
    int k = 0;
    int c = 0;
    spacial_vector mat_mult_row = spacial_vector::Zero(1, n*n);
    std::cout << "Row:\n" << mat_mult_row << std::endl;
    //for each i,j in solution grid
    for(int i = 0; i < n; i++){ // iterate over solution grid
        for(int j = 0; j < n; j++){ // iterate over solution grid
            mat_mult_row = spacial_vector::Zero(1, n*n);
            k=0;
            for(int ii = 0; ii < n; ii++){ // iterate over grid
                for(int jj = 0; jj < n; jj++){ // iterate over grid
            
                    //check adjacency
                    if(i == ii && j == jj){
                        mat_mult_row(0, k++)  = -4;
                        puts("1");
                    } else if(i-1 == ii && j == jj){
                        mat_mult_row(0, k++)  = 1;
                        puts("2");
                    }else if(i+1 == ii && j == jj){
                        mat_mult_row(0, k++)  = 1;
                        printf("3: (i,j) = (%d, %d) (ii, jj) = (%d, %d)\n", i, j, ii, jj);;
                    }else if(i == ii && j-1 == jj){
                        mat_mult_row(0, k++)  = 1;
                        puts("4");
                    }else if(i == ii && j+1 == jj){
                        mat_mult_row(0, k++)  = 1;
                        printf("5: (i,j) = (%d, %d) (ii, jj) = (%d, %d)\n", i, j, ii, jj);
                    }else{
                        mat_mult_row(0, k++)  = 0;
                        printf("5: (i,j) = (%d, %d) (ii, jj) = (%d, %d)\n", i, j, ii, jj);
                    }
                    

                }
            }
            
            std::cout << "Row:\n" << mat_mult_row << std::endl;
             
            lp_matrix.block(c++,0,1, n*n) = mat_mult_row;
            
            std::cout << "LP:\n" << lp_matrix << std::endl;
             
        }
       
     
        
    }
    
    return lp_matrix;

    
}


int main(int argc, char **argv){
    
    
    float x_tmp;
    float y_tmp;
    

    twoDGrid grid = twoDGrid::Zero(100, 100); //finite difference stencil. Typical algorithms will solve the Laplacian iterating inward from the boundary conditions.  
    
    
    int n = 3;
    
    
    Laplacian lp_matrix = Laplacian::Zero(n, n);
    
    lp_matrix = construct_laplacian_matrix(n);
    
    
    
    
    std::cout << "***************OUTPUT***************:\n"  << std::endl;
    std::cout << "The Laplacian discrete operator matrix:\n" << lp_matrix << std::endl;
    
    
}
    