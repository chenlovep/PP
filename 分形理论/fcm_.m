function [ center, U, obj_fcn ] = fcm_( img, cluster_n, options )
%��imgͼ�����fcm���࣬cluster_n������Ŀ
%����ͼ��img
if nargin ~= 2 & nargin ~= 3
    error('Too many or too few input arguments'); 
end

[r,c,channel] = size(img);
%r*cΪ�������������
%����3Ϊ�����������˴�Ϊlab������rgb����
data = zeros(r*c, channel);
for i=1:r
    for j=1:c
        data((i-1)*c+j,1) = img(i,j,1);
        data((i-1)*c+j,2) = img(i,j,2);
        data((i-1)*c+j,3) = img(i,j,3);
    end
end

%Ĭ�ϲ�������
default_options = [2,100,1e-5,1];
if nargin == 2
    options = default_options;
else
    if length(options) < 4
        tmp = default_options;
        tmp(1:length(options)) = options;
        options = tmp;
    end
    %����options��Ϊnan��ֵΪ1
    nan_index = find(isnan(options) == 1);
    %��default_options�ж�Ӧλ�ò�����ֵ��options�в�������λ��
    options(nan_index) = default_options(nan_index);
    if options(1) <= 1
        error('The exponent should be greater than 1'); 
    end
end

expo = options(1); %�����Ⱦ���U��ָ��
max_iter = options(2); %����������
min_impro = options(3); %��������С�仯����������ֹ����
display = options(4); %�����Ƿ������־��Ϣ

obj_fcn = zeros(max_iter,1);%��ʼ���������obj_fcn
U = initfcm(cluster_n, r*c);%��ʼ��ģ������U(cluster_n, 3),3Ϊ������

for i =1:max_iter
    %�������Ⱥ���U�;�������center���и���
    [U, center, obj_fcn(i)] = stepfcm(data, U, cluster_n, expo);
    
    if i>1
        if abs(obj_fcn(i)- obj_fcn(i-1))<min_impro
            break
        end
    end
end
iter_n = i;
obj_fcn(iter_n+1:max_iter) = [];
end


