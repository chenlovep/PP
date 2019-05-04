function [ U_new, center, obj_fcn ] = stepfcm( data, U, cluster_n, expo )
%ģ��C��ֵ���е���

mf = U.^expo;       % �����Ⱦ������ָ��������

center = mf*data./((ones(size(data, 2), 1)*sum(mf'))'); % 
dist = distfcm(center, data);       % ����������
obj_fcn = sum(sum((dist.^2).*mf));  % ����Ŀ�꺯��ֵ
tmp = dist.^(-2/(expo-1));
U_new = tmp./(ones(cluster_n, 1)*sum(tmp));  % �����µ������Ⱦ��� (5.3)ʽ
end

