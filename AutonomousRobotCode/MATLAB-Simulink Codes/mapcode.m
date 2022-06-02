%%sınırlar belli ediliyor...

length =6;
width =6;

map = binaryOccupancyMap(length,width,10);

%%engel tanımlama
for array2=[3.3:0.01:4.7]
a2=[1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1];
a2 = array2 * a2 ;
b2=[1.7;1.8;1.9;2;2.1;2.2;2.3;2.4;2.5;2.6;2.7;2.8;2.9;3;3.1;3.2;3.3];
setOccupancy(map, [a2 b2], ones(17,1))
end


% %% engeller tanımlanacak 
% 
% % engel-1
% 
% a=[1;1;1;1;1;1;1;1;1;1;1;1;1];
% a = 2.5 * a ;
% b=[0;0.1;0.2;0.3;0.4;0.5;0.6;0.7;0.8;0.9;1;1.1;1.2];
% 
% setOccupancy(map, [a b], ones(13,1))
% 
% c=[1;1;1;1;1;1;1;1;1;1;1;1;1];
% c = 2.6 * c ;
% d=[0;0.1;0.2;0.3;0.4;0.5;0.6;0.7;0.8;0.9;1;1.1;1.2];
% 
% setOccupancy(map, [c d], ones(13,1))
% 
% 
% e=[1;1;1;1;1;1;1;1;1;1;1;1;1];
% e = 2.7 * e ;
% f=[0;0.1;0.2;0.3;0.4;0.5;0.6;0.7;0.8;0.9;1;1.1;1.2];
% 
% setOccupancy(map, [e f], ones(13,1))
% 
% g=[1;1;1;1;1;1;1;1;1;1;1;1;1];
% g = 2.8 * g ;
% h=[0;0.1;0.2;0.3;0.4;0.5;0.6;0.7;0.8;0.9;1;1.1;1.2];
% 
% setOccupancy(map, [g h], ones(13,1))
% show(map)

%% engel-2

x=ones(16,1);
x = 0 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];

setOccupancy(map, [x y], ones(16,1));
show(map)



x=ones(16,1);
x = 0.2 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];


setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 0.3 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 0.4 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 0.5 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];

setOccupancy(map, [x y], ones(16,1));
show(map)



x=ones(16,1);
x = 0.6 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];


setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 0.7 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 0.8 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 0.9 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];

setOccupancy(map, [x y], ones(16,1));
show(map)



x=ones(16,1);
x = 1 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];


setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 1.6 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 1.1 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];





setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 1.2 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];

setOccupancy(map, [x y], ones(16,1));
show(map)



x=ones(16,1);
x = 1.3 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];


setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 1.4 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)

x=ones(16,1);
x = 1.5 * x ;

y= [4.5;4.6;4.7;4.8;4.9;5;5.1;5.2;5.3;5.4;5.5;5.6;5.7;5.8;5.9;6];



setOccupancy(map, [x y], ones(16,1));
show(map)
grid;
xticks(0:0.4:6);
yticks(0:0.4:6);




    %xinit3

    posex5 = 5:0.4:5.8;
    posex6 = 5.8:-0.4:5;
    
    %yinit3
    yones3=ones(1,2);
    posey10      = [yones3 * 3 2.6];
    posey11      = [yones3 * 2.6 2.2];
    posey12      = [yones3 * 2.2 1.8];
    posey13      = [yones3 * 1.8 1.4];


    x_init3=[posex6 posex5 posex6 posex5];

    y_init3= [posey10 posey11 posey12 posey13 ];


% engel-3

for array=[0:0.01:6]
a=[1;1;];
a = array * a ;
b=[0;0.12;];
setOccupancy(map, [a b], ones(2,1))
end
show(map)



