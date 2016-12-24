c_data = [7,4,9,2,8,20,5];

hist_w = length(c_data);
hist_h = max(c_data);

hist_a = zeros(hist_h,hist_w);

freq=1:hist_w;

for d =1:length(c_data)
    c=c_data(d);
    hist_a(hist_h - c+1:hist_h,d)=1;
end

hist_a



for row=1:hist_h
    for col=1:hist_w
        if hist_a(row,col)==1
            fprintf(' * ');
        else
            fprintf('   ');
        end
        if col == hist_w
            fprintf('\n');
        end
    end
end

for f=1:length(freq)
    fprintf('---' ,freq(f));
    
    if f==length(freq)
       fprintf('\n');
    end
    
end

for f=1:length(freq)
    fprintf(' %1.d ' ,freq(f));
    
    if f==length(freq)
       fprintf('\n');
    end
    
end
