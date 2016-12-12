function [  ] = empty_rect(a,b)
%text on dev branch
for row = 1:a % print every row a certain column
    for column = 1: b
        if row == 1||row==a % check for first and last row
            if column ~= b % check for nonlast column in row
                fprintf('%c',('#'));             
            else
                fprintf('%c',('#'));
                fprintf('\n');
            end
        else %print other than 1st or last row
            if column == 1
                fprintf('%c',('#'));
            elseif column==b
                fprintf('%c',('#'));
                fprintf('\n');
            else
                fprintf('%c',(' '));
            end
            
        end
    end
end

