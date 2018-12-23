function seg = imseg( img,Lseg,F )
%IMSEGͼ��ָ�
%SEG=IMSEG��IM��L��F����ͼ��IM�ָ�ɴ����Ͻǿ�ʼ�Ĵ�СΪL��L���ص�����������
%IM��ʣ�ಿ��С��LxL�������������F = 1���ú������������ӻ������֡� 
%���F = 0���򲻴������֡��ú�������SEG��������ͼ��εĵ�Ԫ���С�
if F
    figure;imshow(img);
    figure;
end
L=size(img);
max_row = floor(L(1)/Lseg);
max_col = floor(L(2)/Lseg);
seg = cell(max_row,max_col);

r1=1; %��ǰ�����������Ϊ1
for row =1:max_row
    c1 = 1;%��ǰ�����������Ϊ1
    for col = 1:max_col
        %disp(['--- row/col ' num2str(row) '/' num2str(col)])
        % find end rows/columns for segment�ҵ��εĽ�����/��
        r2 = r1 + Lseg-1;
        c2 = c1 + Lseg-1;
        %�ڵ�Ԫ�����д洢��
        seg(row, col) = {img(r1:r2,c1:c2,:)};
        if F
            subplot(max_row, max_col, (row - 1)*max_col + col)
            imshow(cell2mat(seg(row, col)));
        end
        %����col start index
        c1 = c2 + 1;
    end
    %����row start index
    r1 = r2 + 1;
end
end

