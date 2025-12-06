% Shannon coding

function code = Shann(sym , prob, sig)
n = length(sym);

% sort symbols 
[resym, reprob] = rearr(sym , prob);

% declare Shannon dictionary
Shdict = strings(n, 1);

% word lengths
wordlen = ceil(-log2(reprob));
maxlen = max(wordlen);

% cumulative probabilites & their binary equivalents
cumprob = zeros(size(reprob));
cumprobbin = strings(n, 1);
% for i = 1:numel(cumprobbin) cumprobbin(i) = 'c'; end
for i = 2:n
    cumprob(i) = sum(reprob(1:i-1));
end
for i = 1:n
    cumprobbin(i) = frc2bin(cumprob(i), 2*maxlen);
end

% set Shannon dictionary
cpbtmp = "";     % temprary variable
for i = 1:n
    cpbtmp = cumprobbin(i);
    for j = 1:wordlen(i)
        Shdict(i) = strcat(Shdict(i),extract(cpbtmp, j));
    end
end

% display sShannon dictionary
Shdict

% generate Shannon code
code = "";
N = length(sig);
ctmp = "";  % temprary variable
cloc = 0;   % temprary variable
for i = 1:N
    cloc = resym==sig(i);
    ctmp = Shdict(cloc);
    code = strcat(code, ctmp);
end

end     % end function Shann