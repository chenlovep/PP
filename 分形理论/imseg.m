function seg = imseg( img,Lseg,F )
%IMSEG图像分割
%SEG=IMSEG（IM，L，F）将图像IM分割成从左上角开始的大小为L×L像素的正方形区域。
%IM的剩余部分小于LxL将被丢弃。如果F = 1，该函数将创建可视化的数字。 
%如果F = 0，则不创建数字。该函数返回SEG，即包含图像段的单元阵列。
if F
    figure;imshow(img);
    figure;
end
L=size(img);
max_row = floor(L(1)/Lseg);
max_col = floor(L(2)/Lseg);
seg = cell(max_row,max_col);

r1=1; %当前行索引，最初为1
for row =1:max_row
    c1 = 1;%当前列索引，最初为1
    for col = 1:max_col
        %disp(['--- row/col ' num2str(row) '/' num2str(col)])
        % find end rows/columns for segment找到段的结束行/列
        r2 = r1 + Lseg-1;
        c2 = c1 + Lseg-1;
        %在单元阵列中存储段
        seg(row, col) = {img(r1:r2,c1:c2,:)};
        if F
            subplot(max_row, max_col, (row - 1)*max_col + col)
            imshow(cell2mat(seg(row, col)));
        end
        %增量col start index
        c1 = c2 + 1;
    end
    %增量row start index
    r1 = r2 + 1;
end
end

