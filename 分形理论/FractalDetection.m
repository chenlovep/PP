clear all;
close all;
clc;

epsilon = 5;
%epsilon = 5;
Img = imread('01.jpg');
img_r = Img(:,:,1);
img_r = imresize(img_r, [300 300]);
img_g = Img(:,:,2);
img_g = imresize(img_g, [300 300]);
img_b = Img(:,:,3);
img_b = imresize(img_b, [300 300]);
img = cat(3, img_r, img_g, img_b);
%去噪处理
% filter = ones(5,5);
% filter = filter/sum(filter(:));
% denose_img_r = conv2(img(:,:,1), filter, 'same');
% denose_img_g = conv2(img(:,:,2), filter, 'same');
% denose_img_b = conv2(img(:,:,3), filter, 'same');
% denose_img = cat(3,denose_img_r,denose_img_g,denose_img_b);




img_lab = rgb2lab(img);%将rgb空间转换为lab空间
% C = makecform('srgb2lab');
% img_lab = applycform(img, C);
%img = rgb2gray(imread('15.jpg'));   

cluster_n = 7;%聚类数目

[center, u, obj_fcn] = fcm_(img_lab, cluster_n);
disp(center);
disp(size(u));
%IMG图像为将图像去除部分背景的二进制图像
%根据IMG将每部分图像进行分形维数求解

K = 3;
a = 25;%确定选取区域的大小范围(r*c/a，r*c/(30*a))
[IMG] = show_segment_fcm(img,center,u,K,a );
%img = imread('27.jpg');



% img_gray = rgb2gray(Img);
% [Row,Col] = size(img_gray);
% %img = img(100:Row,1:Col);
% [row,col] = size(img_gray);
% 
% template_size = 5;
% Row = template_size - 1 + row;
% Col = template_size - 1 + col;
% Img_extension = zeros(Row,Col);
% for i = (template_size + 1)/2:Row - (template_size - 1)/2
%     for j = (template_size + 1)/2:Col - (template_size - 1)/2 
%         Img_extension(i,j) = img_gray(i - (template_size + 1)/2 + 1,j - (template_size + 1)/2 + 1);
%     end
% end
% 
% Img_extension = uint8(Img_extension); %类型转换
% 
% Img_template = zeros(template_size, template_size);
% d = zeros(row, col);
% e = zeros(row, col);
% s = zeros(row, col);
% f = zeros(row, col);
% for i = 1:row
%     for j = 1:col
%         Img_template = Img_extension(i:i+template_size - 1,j:j + template_size - 1);
%         [d(i,j),e(i,j),s(i,j)] = myjob(Img_template, epsilon);
%         %[d(i,j),e(i,j),s(i,j)] = FastBlanketLFD(Img_template, epsilon);
%         %d(i,j)=BlanketLFD(Img_template, epsilon);
%         %d(i,j)=BlanketLFD(Img_template.epsilon);
%         f(i,j)=(3-d(i,j))*e(i,j)*s(i,j);
%     end
% end
% D = zeros(ceil(row/template_size), ceil(col/template_size));
% v = zeros(size(D));
% for i=1:ceil(row/template_size)
%     for j=1:ceil(col/template_size)
%         s = 0;S=0;
%         for m = 0:template_size-1
%             for n = 0:template_size-1
%                 s = s + d(i+m, j+n);
%                 S = S + e(i+m, j+n);
%             end
%         end
%         D(i,j) = s;
%         E(i,j) = S;
%     end
% end
% %disp(D);
% 
% 
% figure;
% mesh(flip(D,1));
% set(gca, 'ZDir','reverse');
% figure;
% mesh(flip(d,1));
% set(gca, 'ZDir','reverse');
% figure;
% mesh(flip(e,1));
% set(gca, 'ZDir', 'reverse');
% figure;
% mesh(flip(E,1));
%x = 1:ceil(row/template_size);
%y = 1:ceil(col/template_size);
%[X,Y] = meshgrid(x,y);
%figure;
%disp(d); 
%view(45,45);
%mesh(X,Y,D);
%disp(e);

% figure;
% imshow(d,[]);
% title('分形维数');
% 
% figure;
% imshow(e,[]);
% title('分形误差');
% 
% figure;
% imshow(s,[]);
% title('');
% 
% figure;
% imshow(f,[]);
% title('');

% [X,Y] = meshgrid(row,col);
% Z=d;
% [X,Y,Z] = mesh;
% A = zeros(row,col);
% [r, c] = size(E);
% 
% for i =1:row
%     for j=1:col
%         if d(i,j)<=0.8
%             图1 0.392
%         
%         if E(i,j) > 1150
%             A(i,j) = 255;
%             A(i*template_size:i*template_size+template_size, j*template_size:j*template_size+template_size) = 255; 
%          end
%      end
% end
% 
% 
% 
% disp(A);
% A1=double(A);
% figure;
% imshow(A);
% title('二分法');
% imwrite(A, '二分法结果图.jpg');
% 进行框图
h = 6;%分形维数处理过后目标的数量
H = 4;%分形误差处理过后最终目标的数目
kuagntu(img, IMG,h,H);


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
%}