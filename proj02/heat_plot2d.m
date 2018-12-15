clear all;
close all;

% Read dat from h5 file
x = h5read('./test/ref_2d_4th_gauss.h5', '/x');
y = h5read('./test/ref_2d_4th_gauss.h5', '/y');
sol= h5read('./test/ref_2d_4th_gauss.h5', '/T_sol');

% Reshape output data
n = sqrt(length(x));
x = reshape(x,[n,n]);
y = reshape(y,[n,n]);
sol = reshape(sol,[n,n]);

% Plot 3D plot with 2D case using surf
figure
surf(x, y, sol);
colorbar;
title("2D Heat Equation Solution Using Gauss-Seidel, 4th order, N = 128 (surf)");
xlabel('x');
ylabel('y');
zlabel('T\_sol');
saveas(gcf, '2D_plot_surf.png');

% Plot 2D plot with 2D case using contour
figure
contourf(x, y, sol);
colorbar;
title("2D Heat Equation Solution Using Gauss-Seidel, 4th order, N = 128 (contour)");
xlabel('x');
ylabel('y');
saveas(gcf, '2D_plot_contour.png');
