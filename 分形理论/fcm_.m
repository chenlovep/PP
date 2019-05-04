function [ center, U, obj_fcn ] = fcm_( img, cluster_n, options )
%将img图像进行fcm聚类，cluster_n聚类数目
%输入图像img
if nargin ~= 2 & nargin ~= 3
    error('Too many or too few input arguments'); 
end

[r,c,channel] = size(img);
%r*c为所有样本点个数
%其中3为特征个数，此处为lab分量或rgb分量
data = zeros(r*c, channel);
for i=1:r
    for j=1:c
        data((i-1)*c+j,1) = img(i,j,1);
        data((i-1)*c+j,2) = img(i,j,2);
        data((i-1)*c+j,3) = img(i,j,3);
    end
end

%默认操作参数
default_options = [2,100,1e-5,1];
if nargin == 2
    options = default_options;
else
    if length(options) < 4
        tmp = default_options;
        tmp(1:length(options)) = options;
        options = tmp;
    end
    %返回options中为nan的值为1
    nan_index = find(isnan(options) == 1);
    %将default_options中对应位置参数赋值给options中不是数的位置
    options(nan_index) = default_options(nan_index);
    if options(1) <= 1
        error('The exponent should be greater than 1'); 
    end
end

expo = options(1); %隶属度矩阵U的指数
max_iter = options(2); %最大迭代次数
min_impro = options(3); %隶属度最小变化量，迭代终止条件
display = options(4); %迭代是否输出标志信息

obj_fcn = zeros(max_iter,1);%初始化输出参数obj_fcn
U = initfcm(cluster_n, r*c);%初始化模糊矩阵U(cluster_n, 3),3为特征数

for i =1:max_iter
    %对隶属度函数U和聚类中心center进行更新
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


