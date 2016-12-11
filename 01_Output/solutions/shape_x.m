function [  ] = shape_x( size )
%SHAPE_Z Summary of this function goes here
%   Detailed explanation goes here

printTopBottom (size);
fprintf('\n');

printDiag(size);
 %printTwoAtPos(7,7)
printTopBottom (size);
%fprintf('\n');
end

function [] = printTopBottom (size)

for i=1:size
    fprintf('%c',('#'));
end

end

function [] = printDiag(size)
for row=2:size-1
    printTwoAtPos(row,size);
    fprintf('\n');
end

end
function [] = printTwoAtPos(pos,len)
for c=1:len
    if c==pos || c==len-pos+1
        fprintf('%c','#')
    else
        fprintf('%c',' ')
    end
end

end