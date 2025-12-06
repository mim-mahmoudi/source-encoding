% Huffman coding

function code = Huff(sym , prob, sig)
% Hdict = huffmandict(sym,prob);
n = length(sym);

% sort symbols 
[resym, reprob] = rearr(sym , prob);

% declare Huffman dictionary
Hdict = strings(n, 1);

% reduced sources
rssym = zeros(n, n-1);
rsprob = zeros(n, n-1);
rscod = strings(n, n-1);
% for i = 1:numel(rscod) rscod(i) = 'c'; end

rssym(:, 1) = (1:n)';
rsprob(:, 1) = reprob;

ptmp = 0;   % temprary variable
% sorting symbols and prbabilites
for k = 2:n-1
    ptmp = sum(rsprob(n-k+1:n-k+2, k-1));

    rssym(1:n-k+1, k) = rssym(1:n-k+1, k-1);
    rsprob(1:n-k, k) = rsprob(1:n-k, k-1);
    rsprob(n-k+1, k) = ptmp;

    [rssym(1:n-k+1, k), rsprob(1:n-k+1, k)] = rearr(rssym(1:n-k+1, k), rsprob(1:n-k+1, k));
end


sloc = 0;   % temprary variable
% determine codes
rscod(1:2, n-1) = ['0'; '1'];
for l = n-2:-1:1
    for p = 1:n-l
        sloc = find(rssym(1:n-l+1, l)==rssym(p, l+1));
        if sloc == n-l
            rscod(sloc, l) = strcat(rscod(p, l+1), '0');
            rscod(sloc+1, l) = strcat(rscod(p, l+1), '1');
        else
            rscod(sloc, l) = rscod(p, l+1);
        end
    end
end

% set Huffman dictionary
Hdict(:, 1) = rscod(:,1)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% code = huffmanenco(sig,dict);

code = "";
N = length(sig);

% temprary variable
ctmp = "";
cloc = 0;
for i = 1:N
    cloc = resym==sig(i);
    ctmp = Hdict(cloc);
    code = strcat(code, ctmp);
end

end     % end function Huff