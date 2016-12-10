function [ ] = speacial_pattern( n )
%SPEACIAL_PATTERN Summary of this function goes here
%   Detailed explanation goes here


for i=1:n
 if ~mod(i,2)<1
    fprintf('%c',' ');
 end
    print_row(n);    
end

end

function [] = print_row(len)

for i=1:len
    fprintf('%c','#*');
end
fprintf('\n');

end