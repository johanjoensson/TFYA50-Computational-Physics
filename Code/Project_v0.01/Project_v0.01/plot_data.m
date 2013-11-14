function plot_data(filename, delimiter)
A = tdfread(filename,delimiter);

plot(A, A.msd)