function [ D,E ] = fenxingweishu( img )
%
%img = uint8(img);
epsilon = 5;
[r,c] = size(img);
template_size = 5;
Row = template_size - 1 + r;
Col = template_size - 1 + c;
Img_extension = zeros(Row,Col);
for i = (template_size + 1)/2:Row - (template_size - 1)/2
     for j = (template_size + 1)/2:Col - (template_size - 1)/2 
         Img_extension(i,j) = img(i - (template_size + 1)/2 + 1,j - (template_size + 1)/2 + 1);
     end
end
% 
d = zeros(r, c);
e = zeros(r, c);
s = zeros(r, c);
f = zeros(r, c);
D = 0;E = 0;
d_ = 0;e_ = 0;
Img_extension = uint8(Img_extension);
for i=1:r
    for j=1:c
        Img_template = Img_extension(i:i+template_size - 1,j:j + template_size - 1);
        [d(i,j),e(i,j),s(i,j)] = myjob(Img_template, epsilon);
        if ~isnan(d(i,j))
            D = D + d(i,j);
            d_ = d_ + 1;
        end
        if ~isnan(e(i,j))
            E = E + e(i,j);
            e_ = e_ + 1;
        end
        
        
        %[d(i,j),e(i,j),s(i,j)] = FastBlanketLFD(Img_template, epsilon);
        %d(i,j)=BlanketLFD(Img_template, epsilon);
        %d(i,j)=BlanketLFD(Img_template.epsilon);
        f(i,j)=(3-d(i,j))*e(i,j)*s(i,j);
    end
end

D = D/d_;
E = E/e_;
end

