clear all;
close all;

A = importdata("/Users/yuegexie/Documents/learn_linux/student-willway1023yx/hw03/integration/integration.txt");
A1 = A(1:15,[2,4]);
A2 = A(16:30,[2,4]);

figure

plot(log(A1(:,1)),log(A1(:,2)),'-o');
title("Asymptotic Convergence Rates for Error Function")
xlabel("log of N")
ylabel("log of abs error")

hold on;
plot(log(A2(:,1)),log(A2(:,2)), '-o');

x1 = [2,12];
y1 = -2*x1;
plot(x1,y1,'--')

x2 = [2,6];
y2 = -4*x2 - 8;
plot(x2,y2,'--')

x3 = [2,12];
y3 = [log(1e-12), log(1e-12)];
plot(x3,y3, '--')

legend('trapezoid','simpson', 'ref line k=-2', 'ref line k=-4', 'ref line y=log(1e-12)')

hold off;
saveas(gcf, 'total.png')

figure

plot(log(A1(:,1)),log(A1(:,2)),'-o');
title("Asymptotic Convergence Rates for Error Function for trapezoid")
xlabel("log of N")
ylabel("log of abs error")

hold on;
x1 = [2,12];
y1 = -2*x1;
plot(x1,y1,'--')

x3 = [2,12];
y3 = [log(1e-12), log(1e-12)];
plot(x3,y3, '--')

legend('trapezoid', 'ref line k=-2', 'ref line y=log(1e-12)')
hold off;

saveas(gcf, 'trapezoid.png')

figure 
plot(log(A2(:,1)),log(A2(:,2)), '-o');
title("Asymptotic Convergence Rates for Error Function for simpson")
xlabel("log of N")
ylabel("log of abs error")

hold on;
x2 = [2,6];
y2 = -4*x2 - 8;
plot(x2,y2,'--')

x3 = [2,12];
y3 = [log(1e-12), log(1e-12)];
plot(x3,y3, '--')
legend('simpson', 'ref line k=-4', 'ref line y=log(1e-12)')
hold off;
saveas(gcf, 'simpson.png')