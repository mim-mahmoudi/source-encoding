% sort symbols 
function [rsym, rprob] = rearr(sym , prob)
rsym = sym;
rprob = prob;
m = length(sym);

% temprary variables
stmp = 0;
ptmp = 0;

for i = 1:m
    for j = i:m
        if rprob(j) > rprob(i)
            stmp = rsym(i);
            ptmp = rprob(i);
            
            rsym(i) = rsym(j);
            rprob(i) = rprob(j);
            
            rsym(j) = stmp;
            rprob(j) = ptmp;
        end
    end
end
end