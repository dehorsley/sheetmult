mex sheetmulti.c -lmwblas

MN = 101*100;
Kth = 201;
Kr = 102;

R = randn(MN,Kth,Kr);
A = randn(MN,1);

tic
P1 = zeros(Kth,Kr);
for i=1:Kr
    P1(:,i) = R(:,:,i)'*A;
end
toc

tic
P2 = sheetmulti(A,R);
toc

norm(P1-P2)
