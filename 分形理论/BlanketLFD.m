function D = BlanketLFD(Imag, epsilon)
% Imag = rgb2gray(imread('t1.jpg'));epsilon=10;
[row,col] = size(Imag);
U = zeros(row,col,epsilon);
B = zeros(row,col,epsilon);
%��ʼ����̺�Ӻ��epsilonΪ0ʱ���������涨��Ϊԭʼ����Ҷ�
U(:,:,1) = Imag;%U�ϱ���
B(:,:,1) = Imag;%B�±���

for p = 2:epsilon
   for j = 1:col
       for i = 1:row
           %����(i,j)����ϡ��¡������ĸ�����
           if i==1
               up = i;
           else
               up = i-1;
           end
           if j==1
               left = j;
           else
               left = j-1;
           end
           if i==row
               down = i;
           else
               down = i+1;
           end
           if j == col
               right = j;
           else
               right = j+1;
           end
           U(i,j,p) = max(U(i,j,p-1)+1,max(U(i,j,p-1),max(max(U(up,j,p-1),U(i,left,p-1)),max(U(down,j,p-1),U(i,right,p-1)))));
           B(i,j,p) = min(B(i,j,p-1)-1,min(B(i,j,p-1),min(min(B(up,j,p-1),B(i,left,p-1)),min(B(down,j,p-1),B(i,right,p-1)))));
       end
   end
end
%�������
Volume = zeros(epsilon,1);
V_temp = zeros(row,col);

for p = 1:epsilon
    V_temp(:,:) = U(:,:,p)-B(:,:,p);
    Volume(p,1) = sum(sum(V_temp));
end
%��������ͼ������
Area = zeros(1,epsilon);
Area(1,1) = 1;
for p=2:epsilon
    Area(1,p) = Volume(p,1)/2*p; 
end
%��Ϸ�ά
log_x = log(1:epsilon);
log_y = log(Area);
K = polyfit(log_x(2:epsilon),log_y(2:epsilon),1);
D = 2-K(1);

%%
%������
%i=2:epsilon;
%X=[1,i-1];
%Ksum=0;
%Logepsilon=log(X);
%LogArea=log(Area);
%for i=3:42   %��ȥ�˵�1��2����
%K=polyfit(Logepsilon(i:i+2),LogArea(i:i+2),1);
%Ksum=Ksum+K(1);
%end
%Kave=Ksum/40;
%D=-Kave+2;  %����ά��
