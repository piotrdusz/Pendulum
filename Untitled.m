clc
clear



syms m0 m1 m2 mA mB;
syms l1 l2 g;
syms F;
syms fi1 dfi1 ddfi1;
syms fi2 dfi2 ddfi2;
syms x0; syms dx0 ddx0;
syms IA IB;
syms b0 b1 b2;

%T=0.5*(m0+m1)*dx0^2-m1*l*dx0*dfi*cos(fi)+0.5*m1*(dfi)^2*l^2+0.5*IA*dfi^2;
%U=m1*g*l*cos(fi)+mA*g*l/2*cos(fi);

V1=(dx0-dfi1*l1*cos(fi1))^2+(-dfi1*l1*sin(fi1))^2;

V2=(dx0-dfi1*l1*cos(fi1)-dfi2*l2*cos(fi2))^2+(-dfi1*l1*sin(fi1)-dfi2*l2*sin(fi2))^2;

T=0.5*m0*dx0^2+0.5*m1*V1+0.5*IA*dfi1^2+0.5*m2*V2+0.5*IB*dfi2^2;
U=m1*g*l1*cos(fi1)+mA*g*l1/2*cos(fi1)+m2*g*(l2*cos(fi2)+l1*cos(fi1))+mA*g*(l2/2*cos(fi2)+l1*cos(fi1));

L=T-U;


Equations=Lagrange(L,[x0,dx0,ddx0,fi1,dfi1,ddfi1,fi2,dfi2,ddfi2]);

ok1=Equations(1)-F+b0*dx0;
ok2=Equations(2)+b1*dfi1;
ok3=Equations(3)+b2*dfi2;

solf=solve(ok1,ok2,ok3,ddx0,ddfi1,ddfi2);
roz_ddx=ccode(solf.ddx0);
roz_ddfi1=ccode(solf.ddfi1);
roz_ddfi2=ccode(solf.ddfi2);


%linearyzacja rownan
i1=subs(ok1,{dfi1^2,cos(fi1),sin(fi1),dfi2^2,cos(fi2),sin(fi2),cos(fi1 - fi2)},{0,1,fi1,0,1,fi2,1})
i2=subs(ok2,{dfi1^2,cos(fi1),sin(fi1),dfi2^2,cos(fi2),sin(fi2),cos(fi1 - fi2)},{0,1,fi1,0,1,fi2,1})
i3=subs(ok3,{dfi1^2,cos(fi1),sin(fi1),dfi2^2,cos(fi2),sin(fi2),cos(fi1 - fi2)},{0,1,fi1,0,1,fi2,1})

solx=solve(i1,i2,i3,ddx0,ddfi1,ddfi2);

x0dd=solx.ddx0;
fi1dd=solx.ddfi1;
fi2dd=solx.ddfi2;


x0dd_xd=subs(x0dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,1,0,0,0,0,0});
x0dd_fi1=subs(x0dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,1,0,0,0,0});
x0dd_fi1d=subs(x0dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,1,0,0,0});
x0dd_fi2=subs(x0dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,1,0,0});
x0dd_fi2d=subs(x0dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,0,1,0});
x0dd_F=subs(x0dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,0,0,1});

fi1dd_xd=subs(fi1dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,1,0,0,0,0,0});
fi1dd_fi1=subs(fi1dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,1,0,0,0,0});
fi1dd_fi1d=subs(fi1dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,1,0,0,0});
fi1dd_fi2=subs(fi1dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,1,0,0});
fi1dd_fi2d=subs(fi1dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,0,1,0});
fi1dd_F=subs(fi1dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,0,0,1});

fi2dd_xd=subs(fi2dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,1,0,0,0,0,0});
fi2dd_fi1=subs(fi2dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,1,0,0,0,0});
fi2dd_fi1d=subs(fi2dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,1,0,0,0});
fi2dd_fi2=subs(fi2dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,1,0,0});
fi2dd_fi2d=subs(fi2dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,0,1,0});
fi2dd_F=subs(fi2dd,{x0,dx0,fi1,dfi1,fi2,dfi2,F},{0,0,0,0,0,0,1});

A = [0      1              0           0    0   0;
     0    x0dd_xd        x0dd_fi1   x0dd_fi1d  x0dd_fi2   x0dd_fi2d;
     0      0          0     1       0           0;
     0    fi1dd_xd       fi1dd_fi1  fi1dd_fi1d  fi1dd_fi2   fi1dd_fi2d;
     0      0          0     0       0           1;
     0    fi2dd_xd       fi2dd_fi1  fi2dd_fi1d  fi2dd_fi2   fi2dd_fi2d;]

 B = [     0;
     x0dd_F;
          0;
        fi1dd_F;
        0;
        fi2dd_F;
        
        ]
C = [1 0 0 0 0 0;
     0 0 1 0 0 0;
     0 0 0 0 1 0
     ];
D = [0;
     0;
     0;];
 
  B=subs(B,{m1,m2,m0,mA,mB,l1,l2,g,IA,IB,b0,b1,b2},{0.2,0.2,0.5,0.1,0.1,0.3,0.3,9.8,0.006,0.006,0.1,0,0});
  A=subs(A,{m1,m2,m0,mA,mB,l1,l2,g,IA,IB,b0,b1,b2},{0.2,0.2,0.5,0.1,0.1,0.3,0.3,9.8,0.006,0.006,0.1,0,0});

 
  Q = C'*C;
 Q(1,1) = 20000;
Q(3,3) = 100;
R = 1;
K = lqr(A,B,Q,R)
 

Ac = [(A-B*K)];
Bc = [B];
Cc = [C];
Dc = [D];

states = {'x' 'x_dot' 'phi1' 'phi1_dot' 'phi2' 'phi2_dot'};
inputs = {'r'};
outputs = {'x'; 'phi1'; 'phi2'};

sys_cl = ss(Ac,Bc,Cc,Dc,'statename',states,'inputname',inputs,'outputname',outputs);

t = 0:0.01:5;
r =0.2*ones(size(t));
[y,t,x]=lsim(sys_cl,r,t);
[AX,H1,H2] = plotyy(t,y(:,1),t,y(:,2),'plot');
set(get(AX(1),'Ylabel'),'String','cart position (m)')
set(get(AX(2),'Ylabel'),'String','pendulum angle (radians)')
title('Step Response with LQR Control')







%{

dla pojedynczego

xdd_xd=subs(xdd,{x0,dx0,fi,dfi,F},{0,1,0,0,0});
xdd_fi=subs(xdd,{x0,dx0,fi,dfi,F},{0,0,1,0,0});
xdd_F=subs(xdd,{x0,dx0,fi,dfi,F},{0,0,0,0,1});

fidd_xd=subs(fidd,{x0,dx0,fi,dfi,F},{0,1,0,0,0});
fidd_fi=subs(fidd,{x0,dx0,fi,dfi,F},{0,0,1,0,0});
fidd_F=subs(fidd,{x0,dx0,fi,dfi,F},{0,0,0,0,1});
    
A = [0      1              0           0;
     0    xdd_xd            xdd_fi   0;
     0      0              0           1;
     0 fidd_xd       fidd_fi  0];
B = [     0;
     xdd_F;
          0;
        fidd_F];
C = [1 0 0 0;
     0 0 1 0];
D = [0;
     0];
  
 B=subs(B,{m1,m0,mA,l,g,IA,b1,b2},{0.2,0.5,0.1,0.3,9.8,0.006,0.1,0.1});
 A=subs(A,{m1,m0,mA,l,g,IA,b1,b2},{0.2,0.5,0.1,0.3,9.8,0.006,0.1,0.1});

 Q = C'*C;
 Q(1,1) = 5000;
Q(3,3) = 100;
R = 1;
K = lqr(A,B,Q,R)
%}
