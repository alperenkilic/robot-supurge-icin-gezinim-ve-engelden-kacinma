map = binaryOccupancyMap(map);
robotPose = Pose;
thetaIdx = 3;
% Translation
xyz = robotPose;
xyz(:, thetaIdx) = 0;
    show(map)
    hold on;
    plot(robotPose(:, 1), robotPose(:, 2),'-b')
    drawnow;
    hold off;


