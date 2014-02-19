mex sheetmult.c -lmwblas
mex sheetmultip.c -lmwblas

MN = 101*100;
Kth = 201;
Kr = 102;

R = randn(MN,Kth,Kr);
A = randn(MN,1);
b = 0;

tic
P1 = zeros(Kth,Kr);
for i=1:Kr
    P1(:,i) = R(:,:,i)'*A + b*P1(:,i);
end
toc

tic
P2 = sheetmulti(A,R);
toc

tic
P3 = zeros(Kth,Kr);
P3 =sheetmultip(A,R,P3,b);
toc

norm(P1-P2)
norm(P1-P3)
