function U = initfcm( cluster_n, data_n )
%cluster_n ----- �����
%data_n    ----- ������
%��һ����ʼ�����Ⱦ���U
U = rand(cluster_n, data_n);
col_sum = sum(U);
U = U./col_sum(ones(cluster_n, 1), :);

end

