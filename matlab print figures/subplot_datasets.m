close all
%testfiledir - what is the datasets directory path? Type it in ' ' below
testfiledir = 'TYPE THE PATH HERE';
%this searches the directory for any .txt files and puts info about them in files struct
files = dir(fullfile(testfiledir, '*.txt'));
%create a figure with a name
figure('Name', 'Disctance measurements');
%loop through all .txt files
for i = 1 : length(files)
    %load measurement data into dataset struct
    dataset = importdata( fullfile(testfiledir, files(i).name), ' ');
    %create subplot grid based on the number of files to graph
    subplot( min(3,ceil(length(files)/3)), ceil( length(files)/min(3,ceil(length(files)/3)) ), i ) 
    %plot a line graph with markers for data points
    plot((dataset(:,1)-dataset(1,1))/1000000, dataset(:,2), ...
        Color='#000000', ...
        MarkerEdgeColor='#000000', ...
        Marker="x", MarkerSize=6);
    %show labels for axis
    xlabel('time since start [s]');
    ylabel('distance [m]');
    %show title
    title( erase(files(i).name, ".txt") );
end