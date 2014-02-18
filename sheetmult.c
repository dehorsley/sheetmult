#include <math.h>
#include "mex.h"

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double *A, *R, *X;
    int MN,Kr,Kth;
    int n,m,r,th;

    double* Xr;

    char *chn = "N";
    char *cht = "T"; 
    mwSize* dimR;
    
    dimR = mxGetDimensions(prhs[1]);

    A = mxGetPr(prhs[0]); /* (N*M) x 1 vector */
    R = mxGetPr(prhs[1]); /* N*M x Kth x Kr */

    NM = mxGetN(prhs[0]);
    Kth = dimR[1];
    Kr = dimR[2];

    plhs[0] = mxCreateDoubleMatrix(Kth,Kr,mxREAL);

    X = mxGetPr(plhs[0]);

    for(r=0; r<Kr; r++)
    {
       Xr =  X + Kth*Kr*r*sizeof (double);
    }
}
