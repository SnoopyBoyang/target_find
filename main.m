clear
close all

% 读取图片
%I=imread('tu4.bmp');
I=imread('上.bmp');
figure(1)
imshow(I);
title('原图');

% 获取原图尺寸，转二值图
[M,N,C]=size(I);
I_bw=im2bw(I);
figure(2)
imshow(I_bw);
title('二值图');

% 去噪声，对象像素面积少于5的去除
I_bw=bwareaopen(I_bw,5);
figure(3)
imshow(I_bw);
title('去噪');

% 标定
STATS = regionprops(I_bw,'basic');
% 定义位置坐标
locat_cent=round(N/2);
locat_left=locat_cent-0.05*N;
locat_right=locat_cent+0.05*N;

% 获取对象中心坐标
leg=STATS(1).Centroid(1);

% 判断位置
if leg<=locat_left
    res_locat='左边';
elseif leg>=locat_right
    res_locat='右边';
else
    res_locat='中间';
end

% 结果显示
figure(4)
imshow(I_bw);
title(sprintf('定位，目标在：%s',res_locat));
hold on
rectangle('Position',STATS(1).BoundingBox,'EdgeColor','r') 
hold off

fprintf('对象在横轴位置：%f\n',leg);
