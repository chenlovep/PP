clear all;
close all;

epsilon = 10;
%epsilon = 5;

img = rgb2gray(imread('1.jpg'));   
%img = imread('27.jpg');


[Row,Col] = size(img);
img = img(100:Row,1:Col);
[row,col] = size(img);

template_size = 5;
Row = template_size - 1 + row;
Col = template_size - 1 + col;
Img_extension = zeros(Row,Col);
for i = (template_size + 1)/2:Row - (template_size - 1)/2
    for j = (template_size + 1)/2:Col - (template_size - 1)/2 
        Img_extension(i,j) = img(i - (template_size + 1)/2 + 1,j - (template_size + 1)/2 + 1);
    end
end

Img_extension = uint8(Img_extension); %类型转换

Img_template = zeros(template_size, template_size);
d = zeros(row, col);
e = zeros(row, col);
s = zeros(row, col);
f = zeros(row, col);
for i = 1:row
    for j = 1:col
        Img_template = Img_extension(i:i+template_size - 1,j:j + template_size - 1);
        [d(i,j),e(i,j),s(i,j)] = myjob(Img_template, epsilon);
        %[d(i,j),e(i,j),s(i,j)] = FastBlanketLFD(Img_template, epsilon);
        %d(i,j)=BlanketLFD(Img_template, epsilon);
        %d(i,j)=BlanketLFD(Img_template.epsilon);
        f(i,j)=(3-d(i,j))*e(i,j)*s(i,j);
    end
end
D = zeros(ceil(row/template_size), ceil(col/template_size));
for i=1:ceil(row/template_size)
    for j=1:ceil(col/template_size)
        s = 0;S=0;
        for m = 0:template_size-1
            for n = 0:template_size-1
                s = s + d(i+m, j+n);
                S = S + e(i+m, j+n);
            end
        end
        D(i,j) = s;
        E(i,j) = S;
    end
end
%disp(D);
figure;
mesh(flip(D,1));
set(gca, 'ZDir','reverse');
figure;
mesh(flip(d,1));
set(gca, 'ZDir','reverse');
figure;
mesh(flip(E,1));
%x = 1:ceil(row/template_size);
%y = 1:ceil(col/template_size);
%[X,Y] = meshgrid(x,y);
%figure;
%disp(d); 
%view(45,45);
%mesh(X,Y,D);
%disp(e);

figure;
imshow(d,[]);
figure;
imshow(e,[]);
figure;
imshow(s,[]);
figure;
imshow(f,[]);

%[X,Y] = meshgrid(row,col);
%Z=d;
%[X,Y,Z] = mesh;
A = zeros(row,col);
[r, c] = size(E);
for i =1:row
    for j=1:col
        %if d(i,j)<=0.4  0.35 0.32 %图1 0.392
         if d(i,j)<=0.392
        %if E(i,j) > 1150
            A(i,j) = 255;
            %A(i*template_size:i*template_size+template_size, j*template_size:j*template_size+template_size) = 255; 
        end
    end
end


disp(A);
A1=double(A);
figure;
title('二分法');
imshow(A)
imwrite(A, '二分法结果图.jpg');
%进行框图

kuagntu(img, A);


%I= rgb2gray(imread('1.jpg'));
% height=size(img,1);%求出行
% width=size(img,2);%求出列
% region_size=100;%区域宽高大小
% numRow=round(height/region_size);%图像在垂直方向能分成多少个大小为region_size
% numCol=round(width/region_size);%图像在水平方向能分成多少个大小为region_size
% img=imresize(img,[numRow*region_size,numCol*region_size]);%重新生成新的图像，以防止temp下标越界
% 
% t1=(0:numRow-1)*region_size+1;t2=(1:numRow)*region_size;
% t3=(0:numCol-1)*region_size+1;t4=(1:numCol)*region_size;
% for i=1:numRow
%     for j=1:numCol
%         temp=img(t1(i):t2(i),t3(j):t4(j));
%         figure;
%         inshow(temp);
%     end
% end
% 
% epsilon=7;
% seg_width=25;
% %img=rgb2gray(imread('1.jpg'));
% seg=imseg(img,seg_width,1);
% [seg_row,seg_col]=size(seg);
% img_output=zeros(size(cell2mat(seg)));
% for i=1:seg_row
%     for j=1:seg_col
%         [d(i,j),e(i,j),s(i,j)]=FastBlanketLFD(cell2mat(seg(i,j)),epsilon);
%         D_img_output((i-1)*seg_width+1:i*seg_width,(j-1)*seg_width+1:j*seg_width)=d(i,j);
%         E_img_output((i-1)*seg_width+1:i*seg_width,(j-1)*seg_width+1:j*seg_width)=e(i,j);
%         S_img_output((i-1)*seg_width+1:i*seg_width,(j-1)*seg_width+1:j*seg_width)=s(i,j);
%         F_img_output((i-1)*seg_width+1:i*seg_width,(j-1)*seg_width+1:j*seg_width)=(3-d(i,j))*e(i,j)*s(i,j);
%     end
% end
% figure
% imshow(D_img_output,[]);
% figure
% imshow(E_img_output,[]);
% figure
% imshow(S_img_output,[]);
% figure
% imshow(F_img_output,[]);
