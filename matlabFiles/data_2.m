syms t;
y = 2 * sin(2*t + pi/3)-2;
z1 = diff(y,1);
z2 = diff(y,2);

%%
A = [0 1; -4 0];
B = [0;0];
C = [1 0];
sin_dt1 = 0.2;
sin_dt2 = 1/30;
sin_dt3 = 0.01;

%%
system_contin = ss(A, B, C, 0);
system_disc1 = c2d(system_contin, sin_dt1);
system_disc2 = c2d(system_contin, sin_dt2);
system_disc3 = c2d(system_contin, sin_dt3);
