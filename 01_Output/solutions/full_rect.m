function [ ] = full_rect( a,b )

for row = 1:a
    for column = 1: b
        if column == b
            % check if its last column, then add new line
            fprintf('%c',('#'));
            fprintf('\n');
        else
           fprintf('%c',('#'));
        end
    end

end
end

