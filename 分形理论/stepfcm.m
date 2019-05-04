function [ U_new, center, obj_fcn ] = stepfcm( data, U, cluster_n, expo )
%模糊C均值进行迭代

mf = U.^expo;       % 隶属度矩阵进行指数运算结果

center = mf*data./((ones(size(data, 2), 1)*sum(mf'))'); % 
dist = distfcm(center, data);       % 计算距离矩阵
obj_fcn = sum(sum((dist.^2).*mf));  % 计算目标函数值
tmp = dist.^(-2/(expo-1));
U_new = tmp./(ones(cluster_n, 1)*sum(tmp));  % 计算新的隶属度矩阵 (5.3)式
end

