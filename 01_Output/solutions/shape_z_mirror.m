function [  ] = shape_z_mirror( size )
%SHAPE_Z Summary of this function goes here
%   Detailed explanation goes here

printTopBottom (size);
fprintf('\n');

printDiag(size);

printTopBottom (size);
fprintf('\n');
end

function [] = printTopBottom (size)

for i=1:size
    fprintf('%c',('#'));
end

end
function [] = printDiag(size)
for row=2:size-1
    printAtPos(row,size);
    fprintf('\n');
end

end
function [] = printAtPos(pos,len)
for c=1:len
    if c==pos
        fprintf('%c','#')
    else
        fprintf('%c',' ')
    end
end

end