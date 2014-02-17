function P = sheetmultml(A,R)
    [NM,Kth,Kr] = size(R);
    P = zeros(Kth,Kr);
    for i=1:Kr
        P(:,i) = A'*R(:,:,i);
    end
end

