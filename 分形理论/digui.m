function [liantong_array,a] = digui(a,i,j,liantong_array)
    %{
    B=[i j];
    [row,col] = size(a);
    while zhan
        zhantou_i = zhan(1);
        zhantou_j = zhan(2);
        zhan(1:2) = [];
        if  and(a(zhantou_i+1,zhantou_j) == 255,and(and(zhantou_i+1>=0,zhantou_i+1<=row),and(zhantou_j>=0,zhantou_j<=col)))
            zhan = [zhan zhantou_i+1 zhantou_j];
            a(zhantou_i+1,zhantou_j) = 0;
            B = [B zhantou_i+1,zhantou_j];
        end
        if  and(a(zhantou_i-1,zhantou_j) == 255,and(and(zhantou_i-1>=0,zhantou_i-1<=row),and(zhantou_j>=0,zhantou_j<=col)))
            zhan = [zhan zhantou_i-1 zhantou_j];
            a(zhantou_i-1,zhantou_j) = 0;
            B = [B zhantou_i-1,zhantou_j];
        end
        if  and(a(zhantou_i,zhantou_j+1) == 255,and(and(zhantou_i>=0,zhantou_i<=row),and(zhantou_j+1>=0,zhantou_j+1<=col)))
            zhan = [zhan zhantou_i zhantou_j+1];
            a(zhantou_i,zhantou_j+1) = 0;
            B = [B zhantou_i,zhantou_j+1];
        end
        if  and(a(zhantou_i, zhantou_j-1) == 255,and(and(zhantou_i>=0,zhantou_i<=row),and(zhantou_j-1>=0,zhantou_j-1<=col)))
            zhan = [zhan zhantou_i zhantou_j-1];
            a(zhantou_i,zhantou_j-1) = 0;
            B = [B zhantou_i,zhantou_j]-1;
  
        end
    end
    %}
    
    [row,col] = size(a);
    if or(or(i<=0,i>row),or(j<=0,j>col))
        return
    end
    
    if a(i,j) == 255
        liantong_array = [liantong_array i j];
        disp(sprintf('连通域点x坐标:%d,y坐标:%d',i,j));
        a(i,j) = 0;
        [liantong_array] = digui(a,i+1,j,liantong_array);
        [liantong_array] = digui(a,i-1,j,liantong_array);
        [liantong_array] = digui(a,i,j+1,liantong_array);
        [liantong_array] = digui(a,i,j-1,liantong_array);
    else
        return
    end
    
end