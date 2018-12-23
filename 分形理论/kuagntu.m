function kuagntu(img, A)

%clc;
%A = imread('二分法结果图.jpg');
figure;
imshow(img);
[row, col] = size(img);
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
disp(num_label);
num_able_label = [];
for i=2:length(num_label)
    if num_label(i) > 200
        num_able_label = [num_able_label i];
    end
end
%符合个数的连通域类别
disp(num_able_label);

disp(length(num_able_label));
for k = 1:length(num_able_label)
    disp(num_able_label(k));
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
    disp(fprintf('第%d个类别属于%d的矩形左上角x坐标:%d,y坐标:%d,长：%d，宽:%d',k,num_able_label(k),min_x,min_y, max_x-min_x,max_y-min_y));
    rectangle('Position',[min_y,min_x, max_y-min_y,max_x-min_x],'LineWidth',1,'EdgeColor','r');
end



%{
%连通域
a = A;
for i=1:row
    for j=1:col
        disp(sprintf('点x坐标为%d,点y坐标为%d', i,j));
        liantong_array = [];
        if A(i,j) == 255
            [liantong_array] = digui(A,i,j,liantong_array);
            if length(liantong_array)>2*20
                disp('True');
                x_ = [];
                y_ = [];
                for m=1:length(liantong_array)
                    if m/2==ceil(m/2)
                        y_ = [y_ liantong_array(m)];
                    else
                        x_ = [x_ liantong_array(m)];
                    end
                end
                min_x = min(min(x_));
                max_x = max(max(x_));
                min_y = min(min(y_));
                max_y = max(max(y_));
                B = [B min_x max_x min_y max_y];
            
            end
        else
            disp('False');
        end
        %disp([i,j]);
    end
end
disp(length(B));

a=1;
b=1;
b=add_(a,b);
disp(b)
%}