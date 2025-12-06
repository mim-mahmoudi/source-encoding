% convert fractional number to its binary representation

function bin = frc2bin(frc, len)

bin = '';
frc2 = 2*frc;   % temprary variable
for i = 1:len
    if frc2 >= 1
        bin = [bin, '1'];
        frc2 = frc2 - 1;
    else
        bin = [bin, '0'];
    end
    frc2 = 2 * frc2;
end

end