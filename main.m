clear
close all

% ��ȡͼƬ
%I=imread('tu4.bmp');
I=imread('��.bmp');
figure(1)
imshow(I);
title('ԭͼ');

% ��ȡԭͼ�ߴ磬ת��ֵͼ
[M,N,C]=size(I);
I_bw=im2bw(I);
figure(2)
imshow(I_bw);
title('��ֵͼ');

% ȥ���������������������5��ȥ��
I_bw=bwareaopen(I_bw,5);
figure(3)
imshow(I_bw);
title('ȥ��');

% �궨
STATS = regionprops(I_bw,'basic');
% ����λ������
locat_cent=round(N/2);
locat_left=locat_cent-0.05*N;
locat_right=locat_cent+0.05*N;

% ��ȡ������������
leg=STATS(1).Centroid(1);

% �ж�λ��
if leg<=locat_left
    res_locat='���';
elseif leg>=locat_right
    res_locat='�ұ�';
else
    res_locat='�м�';
end

% �����ʾ
figure(4)
imshow(I_bw);
title(sprintf('��λ��Ŀ���ڣ�%s',res_locat));
hold on
rectangle('Position',STATS(1).BoundingBox,'EdgeColor','r') 
hold off

fprintf('�����ں���λ�ã�%f\n',leg);
