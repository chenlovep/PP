function [ center, U, obj_fcn ] = FCM(img, cluster_n, options)
%UNTITLED2 �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
%   ����
%data           ------nm����n��������ÿ����������mά����ֵ
%N_cluster      ------��������ʾ�ۺ�������Ŀ�������
%options        ------4*1����
%               ------options(1)�������Ⱦ���U��ָ����>1   ��ȱʡֵ2
%               ------options(2): �Դ��������            ��ȱʡֵ100
%               ------options(3): ��������С�仯����������ֹ������ȱʡֵ1e-5
%               ------options(4): ÿ�ε����Ƿ������Ϣ��־  ��ȱʡֵ1
%���
%center         -------��������
%U              -------�����Ⱦ���
%obj_fcn        -------Ŀ�꺯��ֵ
[r,c] = size(img);
data=zeros(r*c,1);
for i=1:r
    for j=1:c
        data((i-1)*c+j)=double(img(i,j));
    end
end
if nargin ~=2 & nargin~=3   %�жϲ���������4������5��
    error('Too many or too few input arguments');
end

data_n=size(data,1);   %��ʾ��������
in_n=size(data,2);     %��ʾ����ֵ����
%Ĭ�ϲ�������
default_options=[2,100,1e-5,1];
if nargin == 2,
    options=default_options;
else       %������option������ʱ������
    if length(options)<4,  
        tmp=default_options;
        tmp(1:length(options))=options;
        options=tmp;
    end
    %����options��������ֵΪ0��������ʱΪ1
    nan_index=find(isnan(options)==1);
    %��denfault_options�ж�Ӧλ�õĲ�����ֵ��options�в�������λ��
    options(nan_index)=default_options(nan_index);
    if options(1)<=1,
        error('The exponent should be greater than 1');
    end
end
    
%��options�еķ����ֱ�ֵ���ĸ�����
expo=options(1);                  %�����Ⱦ���U��ָ��
max_iter=options(2);              %����������
min_impro=options(3);             %��������С�仯����������ֹ����
display=options(4);               %ÿ�ε����Ƿ������Ϣ��־
obj_fcn=zeros(max_iter,1);        %��ʼ���������obj_fcn

U=initfcm(cluster_n,data_n);      %��ʼ��ģ���������ʹU�����������Ϊ1%UΪ��cluster_n,data_n��
%��ѭ��
for i =1:max_iter
    
    %��ÿһ��ѭ���иı��������ceneter�ͷ��亯��U��������ֵ
    [U,center,obj_fcn(i)] = stepfcm(data,U,cluster_n,expo);
    %if display,
    %    fprintf('FCM:Iteration count=%d,obj.fcn=%f\n',i,obj_fcn(i));
    %end
    
    %��ֹ�����б�
    if i>1,
        if abs(obj_fcn(i)-obj_fcn(i-1))<min_impro,
            break;
        end
        %if sum(sum(abs(U-U0)))<1
        %    break;
        %end
    end
end
iter_n=i;
obj_fcn(iter_n+1:max_iter)=[];
end

