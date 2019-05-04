function U = initfcm( cluster_n, data_n )
%cluster_n ----- 类别数
%data_n    ----- 特征数
%归一化初始隶属度矩阵U
U = rand(cluster_n, data_n);
col_sum = sum(U);
U = U./col_sum(ones(cluster_n, 1), :);

end

