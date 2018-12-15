clear all;
close all;

t = 30:30:360;

% Read time record for 1D
A(:,1) = importdata("./time_record/record_1D_jacobi.txt");
A(:,2) = importdata("./time_record/record_1D_gauss.txt");
A(:,3) = importdata("./time_record/record_1D_gmres.txt");

% Plot
figure
plot(t,A(:,1),'-*');
title("Runtime Performance for 1D Cases");
xlabel('N:number of intervals');
ylabel('T:runtime/s');
hold on
plot(t,A(:,2),'-o');
plot(t,A(:,3),'-s');
legend({"Jacobi","Gauss","GMRES"},'Location','northwest');
hold off
saveas(gcf,'1D_time.png');

% Read time record for 2D
B(:,1) = importdata("./time_record/record_2D_jacobi.txt");
B(:,2) = importdata("./time_record/record_2D_gauss.txt");
B(:,3) = importdata("./time_record/record_2D_gmres.txt");

% Plot
figure
plot(t,B(:,1),'-*');
title("Runtime Performance for 2D Cases");
xlabel('N:number of intervals');
ylabel('T:runtime/s');
hold on
plot(t,B(:,2),'-o');
plot(t,B(:,3),'-s');
legend({"Jacobi","Gauss","GMRES"},'Location','northwest');
hold off
saveas(gcf,'2D_time.png');