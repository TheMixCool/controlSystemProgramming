clear all;
close all;

W = tf([1 1 1 0],[1 2 2 1]);

Ac = [-2 -2 -1; 1 0 0; 0 1 0];
Bc = [2; 0; 0];
Cc = [-0.5 -0.5 -0.5];
Dc = [1];

dt1 = 0.2;
dt2 = 1/30;
dt3 = 0.01;


S =ss(W);

Ad1 = expm(Ac*dt1) ;
Bd1 = inv(Ac)*(Ad1 - eye(3,3)) *Bc;
Cd1 = Cc;
Dd1 = Dc;

Ad2 = expm(Ac*dt2) ;
Bd2 = inv(Ac)*(Ad2 - eye(3,3)) *Bc;
Cd2 = Cc;
Dd2 = Dc;

Ad3 = expm(Ac*dt3) ;
Bd3 = inv(Ac)*(Ad3 - eye(3,3)) *Bc;
Cd3 = Cc;
Dd3 = Dc;