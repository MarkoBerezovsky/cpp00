function [  ] = triangle_up_num(n)
%TRIANGLE_DOWN Summary of this function goes here
%   Detailed explanation goes here
c=1;
for row = 1:n   
    for column = 1:c
        if column == c
            % check if its last column, then add new line
            fprintf('%d',row+1-column);
            fprintf('\n');
        else
           fprintf('%d',row+1-column);
        end
    end
    c=c+1;
end
end

