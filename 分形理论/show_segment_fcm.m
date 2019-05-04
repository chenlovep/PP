function [IMG] = show_segment_fcm(img,center, u, K, a_ )
%K-----���������С��ǰK������
[r,c,channel] = size(img);
img_ = zeros(r,c,3);
disp(fprintf('ͼ���С%d,%d,%d',r,c,channel));
label_img = zeros(r,c);
[cluster_n, data_n] = size(u);
%number_areaȷ��ÿ���ָ���������
number_area = zeros(cluster_n, 1);
for i=1:r
    for j=1:c
        a = find(u(:,(i-1)*c+j) == max(u(:,(i-1)*c+j)));
        label_img(i,j) = a;
        if a==1
            img_(i,j,1) = 255;
            img_(i,j,2) = 0;
            img_(i,j,3) = 0;
            number_area(a,1) = number_area(a,1) + 1;
        elseif a==2
            img_(i,j,1) = 0;
            img_(i,j,2) = 255;
            img_(i,j,3) = 0;
            number_area(a,1) = number_area(a,1) + 1;
        elseif a==3
            img_(i,j,1) = 0;
            img_(i,j,2) = 0;
            img_(i,j,3) = 255;
            number_area(a,1) = number_area(a,1) + 1;
        elseif a == 4
            img_(i,j,1) = 0;
            img_(i,j,2) = 255;
            img_(i,j,3) = 255;
            number_area(a,1) = number_area(a,1) + 1;
        elseif a == 5
            img_(i,j,1) = 255;
            img_(i,j,2) = 0;
            img_(i,j,3) = 255;
            number_area(a,1) = number_area(a,1) + 1;
        elseif a == 6
            img_(i,j,1) = 255;
            img_(i,j,2) = 255;
            img_(i,j,3) = 0;
            number_area(a,1) = number_area(a,1) + 1;
        else
            img_(i,j,1) = 255;
            img_(i,j,2) = 255;
            img_(i,j,3) = 255;
            number_area(a,1) = number_area(a,1) + 1;
        end
    end
end
figure;
imshow(img_);
title('fcm����');
julei_img = zeros(r,c);
%��ÿ��������������ڷ�Χ֮��

          

%���������С��ǰK�����
for k=1:K
    min_area = find(number_area(:,1) == min(number_area(:,1)));
    for i=1:r
        for j=1:c
            if label_img(i,j) == min_area
                julei_img(i,j) = 255;
            end
        end
    end
    number_area(min_area, 1) = inf;
end
% 
% k1 = cluster_n-K;
% for k=1:k1
%     L = zeros(r,c);
%     max_area = find(number_area(:,1) == max(number_area(:,1)));
%     for i=1:r
%         for j=1:c
%             if label_img(i,j) == max_area
%                 L(i,j) = 255;
%             end
%         end
%     end
%     figure
%     imshow(L);
%     title('����������');
%     A = bwlabel(L);
%     disp(A);
%     num_labels = zeros(1,max(max(A))+1);
%     disp(fprintf('��������%d����ͨ��', max(max(A))));
%    
%     for i=1:r
%         for j=1:c
%             num_labels(1,A(i,j)+1) = num_labels(1,A(i,j)+1) + 1;
%         end
%     end
%     disp(num_labels);
%     num_labels(1) = [];%ȥ������
%     for m=1:2
%         b = find(num_labels(1,:) == max(num_labels(1,:)));
%         disp(fprintf('�����������Ϊ��%d',b));
%         for i=1:r
%             for j=1:c
%                 if A(i,j) == b
%                     L(i,j) = 0;
%                 end
%             end
%         end
%         num_labels(1,b) = 0;
%     end
%     figure;
%     imshow(L);
%     title('������������');
%     number_area(max_area, 1) = 0;
%     julei_img = julei_img + L;
% end

figure;
imshow(julei_img);
title('�ϲ�����');

%��ֵ����ͨ����
L = bwlabel(julei_img);
%num_labelÿһ�����
num_label = zeros(1,max(max(L))+1);
num_xy = zeros(1,max(max(L))+1);
for i=1:r
    for j=1:c
        num_label(L(i,j)+1) = num_label(L(i,j)+1) + 1;
    end
end
disp(num_label);
num_able_label = [];
disp(r*c/10);
for i=2:length(num_label)
    if num_label(i) <= r*c/a_ & num_label(i) >= r*c/(a_*30)
        num_able_label = [num_able_label i];
    end
end
disp(num_able_label);
disp(num_label(num_able_label));
IMG = zeros(r,c);
disp(num_label(43));
for i=1:r
    for j=1:c
        if ismember(L(i,j)+1, num_able_label)
             IMG(i,j) = 255;
        end 
    end
end
figure;
imshow(IMG);
title('ȥ������ͼ��');
end

