function yichuanfangchengmax(xi,yi)
num=100;
for i5=1:100
    for j5=1:2
       T(i5,j5)=fix(rand(1)*100);
    end
end
max1=0;
for i=1:100
    if(T(1))
end
for j4=1:temps
%     [f]=evalf(T);
%      x1zhi(j4)=x3;
%     x2zhi(j4)=x4;
%[x5,y5]=find(f==max(f));
    [m,n]=size(T);
    for i=1:m
%     T1(i)=bin2dec(num2str(T(i,1:18)));     
%     T2(i)=bin2dec(num2str(T(i,19:33)));
        sum1=0;%sum1和sum2需要放在j循环前面
        sum2=0;
        for j=1:n
            if(j<19)
                p=1;
                for k1=1:(18-j)
                    p=p*2;
                end
                p=p*T(i,j);
                sum1=sum1+p;
            end
            if(j>=19)
                p1=1;
                for k1=1:(33-j)
                    p1=p1*2;
                end
                p1=p1*T(i,j);
                sum2=sum2+p1;
            end
        end
        T1(i)=sum1;
        T2(i)=sum2;
        x1(i)=-3.0+T1(i)*(12.1-(-3))/(2^18-1);
        x2(i)=4.1+T2(i)*(5.8-(4.1))/(2^15-1);
%     f(i)=evalf(x1(i),x2(i));
        f(i)=21.5+x1(i)*sin(4*pi*x1(i))+x2(i)*sin(20*pi*x2(i));
    end

    max1(j4)=max(f);
    for j=1:size(f,2)
        p(j)=f(j)/(sum(f));
        if(j==1)
            q(j)=p(j);  
        end 
       if(j>1)
           q(j)=p(j)+q(j-1);
       end
    end
    for i1=1:size(f,2)
        r=rand(1,1);
        for j1=1:size(f,2)
            if(j1==1)
                if(r<q(j1))
                   cho(i1,:)=T(j1,:);
                end
            end
            if(j1>1)
                if(q(j1-1)<r<q(j1))
                    cho(i1,:)=T(j1,:);
                    break;
                end
            end
        end
    end
    [cho1]=crossover2(cho,pc,crosspoint);
    [T]=mutate(cho1,pm);
end
% subplot(1,2,1)
%     figure(1);
%     plot(max1)
%     axis([0,1000,0,40])
%     hold on
%     plot(smax,'r')
%     hold off
% % x1zh=-3.0:0.3775:12.1;x2zh=4.1:0.0425:5.8;
%     x1zh=-3.0:0.1775:12.1;x2zh=4.1:0.0225:5.8;
%     [x1,x2]=meshgrid(x1zh,x2zh);
%     f2=21.5+x1.*sin(4*pi.*x1)+x2.*sin(20*pi.*x2);
%     figure(2);
%     surf(x1,x2,f2)
%     shading interp
    [x5,y6]=find(max1==max(max1));
    zhi=max1(y6(1));
%     X1=x1zhi(y6(1));
%     X2=x2zhi(y6(1));
    fprintf('函数的最大值为：%0.5f\n',[zhi]);
end
 function [f]=evalf(T)   %%求适应度
 [m,n]=size(T);
 for i=1:m
%     T1(i)=bin2dec(num2str(T(i,1:18)));     
%     T2(i)=bin2dec(num2str(T(i,19:33)));
    sum1=0;%sum1和sum2需要放在j循环前面
    sum2=0;
    for j=1:n
        if(j<19)
            p=1;
            for k1=1:(18-j)
                p=p*2;
            end
            p=p*T(i,j);
            sum1=sum1+p;
        end
        if(j>=19)
            p1=1;
            for k1=1:(33-j)
                p1=p1*2;
            end
            p1=p1*T(i,j);
            sum2=sum2+p1;
        end
    end
    T1(i)=sum1;
    T2(i)=sum2;
    x1(i)=-3.0+T1(i)*(12.1-(-3))/(2^18-1);
    x2(i)=4.1+T2(i)*(5.8-(4.1))/(2^15-1);
%     f(i)=evalf(x1(i),x2(i));
    f(i)=21.5+x1(i)*sin(4*pi*x1(i))+x2(i)*sin(20*pi*x2(i));
end
%    [x5,y5]=find(f==max(f));
%     x3=x1(y5(1));
%     x4=x2(y5(1));
end
function [cho]=crossover2(cho,pc,crosspoint) %交叉
       [m1,n]=size(cho); 
       ran=rand(1,m1); 
       r=crosspoint; 
       [x,ru]=find(ran<pc); 
       for k=1:(m1/2)
            c1= ceil(length(ru)*rand(1));
            c2=ceil(length(ru)*rand(1));
            if (c1~=c2)
               cho(ru(c1),:)=[cho(ru(c1),[1:r]),cho(ru(c2),[(r+1):n])];        
               cho(ru(c2),:)=[cho(ru(c2),[1:r]),cho(ru(c1),[(r+1):n])];        
% cho(ru(k),:)=cho1(ru(k),:);     
           end
       end
end
function [cho1]=mutate(cho1,pm)    %均匀变异
[m,n]=size(cho1);
%  ran=rand(1,m); 
% %  r=rand(1,3);      %dai gai jin 
% %  rr=floor(n*rand(1,3)+1); 
% % [x,mu]=find(ran<pm); 
for i2=1:size(cho1,1)     
%cho1(mu(k),:)=cho1(mu(k),:)
     ran=rand(1,33); 
     [x,mu]=find(ran<pm);
     if(length(mu)~=0)  
         for j2=1:length(mu)
% [x,mu]=find(ran<pm); 
% cho1(i2,:)=cho1(i2,mu(j2))+1;
             if(cho1(i2,mu(j2))==0)
                 cho1(i2,mu(j2))=1;
             else
                 cho1(i2,mu(j2))=0;
             end   
         end
     end
end
end

function [cho]=select(T,f)
for j=1:size(f,2)
    p(j)=f(j)/(sum(f));
    if(j==1)
        q(j)=p(j);  
    end 
    if(j>1)
        q(j)=p(j)+q(j-1);
    end
end
for i1=1:100
    r=rand(1,1);
    for j1=1:size(f,2)
        if(j1==1)
            if(r<q(j1))
                cho(i1,:)=T(j1,:);
            end
        end
        if(j1>1)
            if(q(j1-1)<r<q(j1))
            cho(i1,:)=T(j1,:);
            break;
            end
        end
    end
end


