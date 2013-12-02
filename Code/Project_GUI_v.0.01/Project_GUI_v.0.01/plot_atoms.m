function plot_atoms()
    f = fopen('titi.txt');
    
    fseek(f,0,'eof');
    filesize = ftell(f);
    frewind(f);
    tmp = fread(f, filesize);
    timesteps = sum(tmp == 10);
    frewind(f);
    
    pattern = '(%f, %f, %f)';
    f1 = 'x';
    f2 = 'y';
    f3 = 'z';
    
    %preallocation of struct array, and initialisation of first line
    temp = fgetl(f);
    line = textscan(temp, pattern);
    atoms = repmat(struct('x', line{1}, 'y', line{2}, 'z', line{3}), timesteps, 1);
    xmax = max(atoms(1).x);
    xmin = min(atoms(1).x);
    ymax = max(atoms(1).y);
    ymin = min(atoms(1).y);
    zmax = max(atoms(1).z);
    zmin = min(atoms(1).z);
    
    % Read the remaining lines of data and store them
    for l = 2:timesteps
        temp = fgetl(f);
        line = textscan(temp, pattern);
        atoms(l).x = line{1};
        xmax = max(max(atoms(l).x, xmax));
        xmin = min(min(atoms(l).x, xmin));
        atoms(l).y = line{2};
        ymax = max(max(atoms(l).y, ymax));
        ymin = min(min(atoms(l).y, ymin));
        atoms(l).z = line{3};
        zmax = max(max(atoms(l).z, zmax));
        zmin = min(min(atoms(l).z, zmin));
    end
    x = atoms(1).x;
    y = atoms(1).y;
    z = atoms(1).z;
    ht = scatter3(x, y, z);
    xlim([xmin xmax*1.25]);
    xlabel('x');
    ylim([ymin ymax*1.25]);
    ylabel('y');
    zlim([zmin zmax*1.25]);
    zlabel('z');
    set(ht,'XDataSource','x');
    set(ht,'YDataSource','y');
    set(ht,'ZDataSource','z');
    while 1
    for l = 1:timesteps
        x = atoms(l).x;
        y = atoms(l).y;
        z = atoms(l).z;
        refreshdata(ht, 'caller');
        drawnow
        pause(0.001);
    end
    end
    
    fclose(f);