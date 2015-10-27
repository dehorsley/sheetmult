Sheetmult
==========

This is a MATLAB C mex program to multiply two "sheets" (3D arrays) together.
Eg:
```matlab
for i=1:N
    P(:,i) = A'*R(:,:,i);
end
```
where all arrays are the appropriate size.

`sheetmult` creates a new array for the resulting product, however there is an
in-place version (`sheetmultip`) which places the result back in the `A`
matrix. This uses some undocumented features of MATLAB to work well with the
copy-on-write mechanism so, due to the nature of these APIs, this may break in
future versions or crash MATLAB. (Tested on 2014a)

