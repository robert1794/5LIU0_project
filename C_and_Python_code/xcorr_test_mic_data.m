%To use this script remove the Idex colum and header rows.


A = csvread('100cm_plus60deg.csv')
disp(A(:,1))
disp(A(:,2))
M_A1 = mean(A(:,1));
M_A2 = mean(A(:,2));
s1NoDc = A(:,1) - M_A1;
s2NoDc = A(:,2) - M_A2;
%Correlation with dc removed
[acor, lag] = xcorr(A(:,1), A(:,2));
[val, idx] = max(acor);
disp('ID of max correlation is')
disp(idx)
%plot(lag, acor)

%Correlation with dc removed
[acor_nodc, lag_nodc] = xcorr(A(:,1), A(:,2));
disp('ID of max correlation is without dc')
[val2, idx2] = max(acor_nodc);
disp(idx2)
plot(lag_nodc, acor_nodc)
%plot(s1NoDc)