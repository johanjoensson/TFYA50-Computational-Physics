function plot_data(filename, delimiter)
A = tdfread(filename,delimiter);

subplot(3,3,1)
plot(A.Time, A.Kinetic_Energy)
title('Kinetic Energy')

subplot(3,3,2)
plot(A.Time, A.Potential_Energy)
title('Potential Energy')

subplot(3,3,3)
plot(A.Time, A.Total_Energy)
title('Total Energy')

subplot(3,3,4)
plot(A.Time, A.Cohesive_Energy)
title('Cohesive Energy')

subplot(3,3,5)
plot(A.Time, A.MSD)
title('Mean square displacement')

subplot(3,3,6)
plot(A.Time, A.Internal_Pressure)
title('Internal Pressure')

subplot(3,3,7)
plot(A.Time, A.Temperature)
title('Temperature')

subplot(3,3,8)
plot(A.Time, A.Debeye_Temperature)
title('Debeye temperature')

subplot(3,3,9)
plot(A.Time, A.Specific_Heat)
title('Specific heat')