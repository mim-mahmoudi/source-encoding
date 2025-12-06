% Shannon-Fano coding

function code = Fano(sym , prob, sig)
n = length(sym);

% sort symbols 
[resym, reprob] = rearr(sym , prob);

% declare Shannon-Fano dictionary
Fdict = Fdic(reprob, 0)

% generate Fano code
code = "";
N = length(sig);
ctmp = "";  % temprary variable
cloc = 0;   % temprary variable
for i = 1:N
    cloc = resym==sig(i);
    ctmp = Fdict(cloc);
    code = strcat(code, ctmp);
end
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%
% determin Fano dictionary
function dic = Fdic(reprob, rl0)

if rl0 == 0
    m = length(reprob);
    dic = strings(m, 1);
    mid = findmid(reprob);
    
    dicl = Fdic(reprob(1:mid), -1);
    dicr = Fdic(reprob(mid+1:end), +1);

    for j = 1:mid       dic(j) = strcat(dic(j), dicl(j));       end
    for j = mid+1:m     dic(j) = strcat(dic(j), dicr(j-mid));   end



elseif rl0 == -1
    m = length(reprob);
    dic = strings(m, 1);
    if m == 1
        dic = "0";
    else
        for j = 1:m     dic(j) = "0"; end

        mid = findmid(reprob);
        dicl = Fdic(reprob(1:mid), -1);
        dicr = Fdic(reprob(mid+1:end), +1);
    
        for j = 1:mid       dic(j) = strcat(dic(j), dicl(j));       end
        for j = mid+1:m     dic(j) = strcat(dic(j), dicr(j-mid));   end
    end



elseif rl0 == +1
    m = length(reprob);
    dic = strings(m, 1);
    if m == 1
        dic = "1";
    else
        for j = 1:m     dic(j) = "1";   end
    
        mid = findmid(reprob);
        dicl = Fdic(reprob(1:mid), -1);
        dicr = Fdic(reprob(mid+1:end), +1);
    
        for j = 1:mid       dic(j) = strcat(dic(j), dicl(j));       end
        for j = mid+1:m     dic(j) = strcat(dic(j), dicr(j-mid));   end
    end
end
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%
% find mid
function mid = findmid(prob)
n = length(prob);

if n == 2
    mid = 1;
else
    pmin = 0;
    nextpmin = 0;
    for i = 1:n-1
        if i == n-1
            mid = i;
            break;
        else
        pmin = min(sum(prob(1:i)), sum(prob(i+1:end)));
        nextpmin = min(sum(prob(1:i+1)), sum(prob(i+2:end)));
        if pmin > nextpmin
            mid = i;
            break;
        end
        end
    end
end
end