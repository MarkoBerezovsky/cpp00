function [  ] = triangle_up(n)
%TRIANGLE_DOWN Summary of this function goes here
%   Detailed explanation goes here
c=1;
for row = 1:n   
    for column = 1: c
        if column == c
            % check if its last column, then add new line
            fprintf('%c',('#'));
            fprintf('\n');
        else
           fprintf('%c',('#'));
        end
    end
    c=c+1;
end
end

