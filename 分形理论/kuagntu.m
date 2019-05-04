function kuagntu(img, A, h,H)
%h-----分形维数处理过后剩余的框的数目
%H-----分形误差处理过厚最终显示的框的数目
%clc;
%A = imread('二分法结果图.jpg');
figure;
imshow(img);
[row, col, channel] = size(img);
img_gray = rgb2gray(img);
for i=1:row
    for j=1:col
        if A(i,j) ~= 0
            A(i,j) = 255;
        end
    end
end

L = bwlabel(A);
num_label = zeros(1,max(max(L))+1);
num_xy = zeros(1,max(max(L))+1);
for i=1:row
    for j=1:col
        num_label(L(i,j)+1) = num_label(L(i,j)+1) + 1;
    end
end

num_able_label = [];
for i=2:length(num_label)
    if num_label(i) > 10
        num_able_label = [num_able_label i];
    end
end
%符合个数的连通域类别
disp(num_able_label);

disp(length(num_able_label));

param_ = zeros(length(num_able_label), 7);

for k = 1:length(num_able_label)
   
    %disp(num_label(num_able_label(k)));
    rectangle_x=[];rectangle_y=[];
    for i =1:row
        for j=1:col
            if L(i,j) == num_able_label(k)-1
                rectangle_x = [rectangle_x i];
                rectangle_y = [rectangle_y j];
            end
        end
    end
    min_x=min(rectangle_x);max_x=max(rectangle_x);
    min_y=min(rectangle_y);max_y=max(rectangle_y);
%     e_1=0;
%     
%     for i=min_x:max_x
%         for j=min_y:max_y
%             if isnan(e(i,j))
%                 e(i,j) = 0; 
%             end
%             e_1=e_1+e(i,j)+1;
%         end
%     end
%   
%     param_(k,1) = e_1/((max_y-min_y)*(max_x-min_x));
%     param_(k,2) = min_x;
%     param_(k,3) = max_x-min_x;
%     param_(k,4) = min_y;
%     param_(k,5) = max_y-min_y;
   
    
    [D,E] = fenxingweishu(img_gray(min_x:max_x, min_y:max_y));%求该块区域的分形维数
    if isnan(D)
        D=0;
    end
    if isnan(E)
        E=0;
    end
    param_(k,1) = D;
    param_(k,2) = E;
    param_(k,3) = min_x;
    param_(k,4) = max_x-min_x;
    param_(k,5) = min_y;
    param_(k,6) = max_y-min_y;
    param_(k,7) = num_able_label(k)-1;
    disp(fprintf('第%d个类别属于%d的矩形左上角x坐标:%d,y坐标:%d,长：%d，宽:%d',k,num_able_label(k),min_x,min_y, max_x-min_x,max_y-min_y));
    disp(fprintf('第%d个类别的分形维数为:%.5f', k, param_(k,1)));
    rectangle('Position',[min_y,min_x, max_y-min_y,max_x-min_x],'LineWidth',1,'EdgeColor','r');
end
houxuan = zeros(h,7);
disp(param_);
for i=1:h
    [x] = find(param_(:,1) == min(param_(:,1)));
    houxuan(i,:) = param_(x,:);
    rectangle('Position',[param_(x,5), param_(x,3), param_(x,6), param_(x,4)], 'LineWidth', 1, 'EdgeColor', 'b');
    param_(x,:) = [];
end
disp(houxuan);
a=[];
for i=1:H
    [X] = find(houxuan(:,2) == min(houxuan(:,2)));
    rectangle('Position',[houxuan(X,5), houxuan(X,3), houxuan(X,6), houxuan(X,4)], 'LineWidth', 1, 'EdgeColor', 'g');
    a=[a houxuan(X,7)];
    houxuan(X,:) = [];
end

disp(a)
C = zeros(row,col);
for k = 1:length(a)
    for i=1:row
        for j=1:col
            if L(i,j)==a(k)
                C(i,j) = 255;
            end
        end
    end
end
figure;
imshow(C);
title('所选区域目标');

