%%---毯子法计算分形维数，函数D = blanketGFD(Imag,epsilon)
%%---输入：Imag 要计算维数的图像(灰度图像)
%%---      epsilon 毯子的厚度
%%---输出：D 分形维数

function [ D E S ] = FastBlanketLFD( Imag, epsilon )
% Imag=rgb2gray(Imag);
[row,col] = size(Imag);
% epsilon = 7;
U=zeros(row,col,epsilon);
B=zeros(row,col,epsilon);
U0=zeros(row,col,1);
B0=zeros(row,col,1);
%初始化，毯子厚度epsilon为0时，两个表面定义为原始表面灰度
U0=Imag;
B0=Imag;       %U上表面，B下表面
Nr = zeros(1,epsilon);
for j = 1:row
    for i =1 :epsilon
        Nr1(1,i) = min((255-max(Imag(j,:)))/i,min(Imag(j,:))/i);
    end
end
for j = 1:col
    for i =1 :epsilon
        Nr2(1,i) = min((255-max(Imag(:,j)))/i,min(Imag(:,j))/i);
    end
end
for i=1:epsilon
    Nr(1,i) = min(Nr1(1,i), Nr2(1,i));
end
log_x = log(1:epsilon);
log_y = log(Nr);
K = polyfit(log_x(1:epsilon),log_y(1:epsilon),1);
D = K(1)+1+K(2)/epsilon;
%D = K(1)+1;
E = 0;
S = K(2);
for i=1:epsilon
    E = E+abs((log(Nr(1,i))-K(1)*log_x(i))); 
end
%{
%第1层毯子(尺度1)的两个表面
for j=1:col
    for i=1:row
        %设置(i,j)点的上、下、左、右四个方向
        if i==1
            up = i;
        else 
            up = i-1;
        end
        if j == 1
            left = j;
        else 
            left = j-1;
        end
        if i == row
            down = i;
        else
            down = i+1;
        end
        if j == col
            right = j;
        else
            right = j+1;
        end
        if abs(i-j)/2 == 0
            U(i,j,1) = max(U0(i,j,1)+1,max(U0(i,j,1),max(max(U0(up,j,1),U0(i,left,1)),max(U0(down,j,1),U0(i,right,1)))));
            B(i,j,1) = min(B0(i,j,1)-1,min(B0(i,j,1),min(min(B0(up,j,1),B0(i,left,1)),min(B0(down,j,1),B0(i,right,1)))));
        else
            U(i,j,1) = Imag(i,j);
            B(i,j,1) = Imag(i,j);
        end
    end
end
%计算各个尺度的表面积
Area = zeros(1,epsilon);
Area(1,1) = sum(sum(U(:,:,1)-B(:,:,1)))/2;
temp=Area(1,1);
for p=2:epsilon
    Area(1,p) = (Area(1,1)+(p-1)*row*col/2)/p;
end
%拟合分维d


K = polyfit(log_x(1:epsilon),log_y(1:epsilon),1);
D = 2-K(1);
S = K(2);


 


%计算分形误差
E = 0;
for p = 2:epsilon
    E = E+(log_y(p)-K(1)*log_x(p)-K(2))*(log_y(p)-K(1)*log_x(p)-K(2));
end
%做曲线
% i=2:epsilon;
% X=[1,i-1];
% Ksum=0;
% Logepsilon=log(X);
% LogArea=log(Area);
% for i=3:42   %除去了第1、2个点
% 
%K=polyfit(Logepsilon(i:i+2),LogArea(i:i+2),1);
% % Ksum=Ksum+K(1);
% % end
% % Kave=Ksum/40;
% % D=-Kave+2;  %分形维数

end
%}
