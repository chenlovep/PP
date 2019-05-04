function [ img_lab ] = rgb2lab( img )
%将rgb空间转换为lab空间
img = double(img);
img_lab = zeros(size(img));
[r,c,channel] = size(img);
disp(fprintf('图像大小为(%d,%d,%d)',r,c,channel));
for i=1:r
    for j=1:c
        R = img(i,j,1);
        G = img(i,j,2);
        B = img(i,j,3);
        X = 0.412*R + 0.357*G + 0.180*B;
        Y = 0.212*R + 0.715*G + 0.07*B;
        Z = 0.019*R + 0.119*G + 0.95*B;
        
        X = X/0.950456;
        Y = Y;
        Z = Z/1.088754;
        
        if X > 0.008856
            fx = X^(1/3);
        else
            fx = 7.787 * X + 16/116;
        end
        
        if Y > 0.008856
            fy = Y^(1/3);
            img_lab(i,j,1) = 116.0*fy - 16;
        else
            fy = 7.787*Y+16/116;
            img_lab(i,j,1) = 903.3*fy;
        end
        if img_lab(i,j,1) < 0
            img_lab(i,j,1) = 0;
        end
        
        if Z > 0.008856
            fz = Z^(1/3);
        else
            fz = 7.787*Z + 16/116;
        end
        
        img_lab(i,j,2) = 500*(fx-fy);
        img_lab(i,j,3) = 200*(fy-fz);
    end
end
figure;
imshow(uint8(img));
title('原图');
figure;
imshow(uint8(img_lab));
title('lab空间');
end

