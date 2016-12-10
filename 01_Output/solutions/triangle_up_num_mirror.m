function [  ] = triangle_up_num_mirror(n)

%TRIANGLE_DOWN Summary of this function goes here
%   Detailed explanation goes here
c=1;
for row = 1:n
    for column=1: n-c
        fprintf('%c',(' '));       
    end 
    for column = 1:c
        if column == c
            % check if its last column, then add new line
            fprintf('%d',column);
            fprintf('\n');
        else
           fprintf('%d',column);
        end
    end
    c=c+1;
end
end

