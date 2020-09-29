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
    
    
    //define solution grid 
    //define boundary grid
    //grid = solution grid U boundary grid
    int k = 0;
    int c = 0;
    spacial_vector mat_mult_row = spacial_vector::Zero(1, n*n);
    //for each i,j in solution grid
    for(int i = 0; i < n; i++){ // iterate over solution grid
        for(int j = 0; j < n; j++){ // iterate over solution grid
            mat_mult_row = spacial_vector::Zero(1, n*n);
            k=0;
            for(int ii = 0; ii < n; ii++){ // iterate over grid
                for(int jj = 0; jj < n; jj++){ // iterate over grid
            
                    //check adjacency
                    if(i == ii && j == jj){
                        mat_mult_row(0, k++)  = -4.0;
                    } else if(i-1 == ii && j == jj){
                        mat_mult_row(0, k++)  = 1.0;
                    }else if(i+1 == ii && j == jj){
                        mat_mult_row(0, k++)  = 1.0;
                    }else if(i == ii && j+1 == jj){
                        mat_mult_row(0, k++)  = 1.0;
                    }else{
                        mat_mult_row(0, k++)  = 0.0;
                    }
                    

                }
            }
            
             
            lp_matrix.block(c++,0,1, n*n) = mat_mult_row;
            
             
        }
       
     
        
    }
    
    return lp_matrix;

    
}


int main(int argc, char **argv){
    
    
    
    int n = 2; //size of grid nxn matrix
    
    
    
    spacial_vector u;
    spacial_vector b = spacial_vector::Zero(n*n,1); //boundary vector
    b(0) = -2.0;
    b(1) = -3.0;
    b(2) = -3.0;
    b(3) = -4.0;
    std::cout << "b:\n" << b  << std::endl;
    
    
    Laplacian lp_matrix = Laplacian::Zero(n, n);
    
    
    
    std::cout << "Constructing Laplacian...";
    lp_matrix = construct_laplacian_matrix(n);
    std::cout << " done. \n"  << std::endl;
     std::cout << "The Laplacian discrete operator matrix:\n" << lp_matrix << std::endl;
    
    std::cout << "Solving linear system for vector solution vector u...";
    u = lp_matrix.colPivHouseholderQr().solve(b);
    std::cout << " done. \n"  << std::endl;
    
    
    std::cout << "***************OUTPUT***************:\n"  << std::endl;
    std::cout << "The Laplacian discrete operator matrix:\n" << lp_matrix << std::endl;
    std::cout << "Solution vector u:\n" << u << std::endl;
    
    
}
    
