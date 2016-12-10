function [ ] = stvorec( size )
%STVOREC Summary of this function goes here
%   Detailed explanation goes here

%fprintf('\n');
printTopBottom(size);
fprintf('\n');
printSide(size);
printTopBottom(size);
fprintf('\n');

end

function [] = printTopBottom (size)


for i=1:size
    
fprintf('%c',(['#']));
end

end
function [] = printSide (size)


%if size > 2
    for j = 1:size-2
    for i=1:size
        if i==1
            fprintf('%c',(['#']));
        elseif i==size
            fprintf('%c\n',(['#']));
        else
            fprintf('%c',([' ']));    
        end
    end

    end
%end

end

