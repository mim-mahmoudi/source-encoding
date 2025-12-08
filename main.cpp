#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "source_encoder.h"

using namespace std;





int main()
{
    senc::symbol_list symbols;

    symbols.insert("a", 1.2);
    symbols.insert("b", 0.2);
    symbols.insert("c", 3.2);
    symbols.insert("d", 3.2);
    symbols.insert("e", 3.2);
    symbols.insert("f", 3.3);
    symbols.insert("g", 1.2);
    symbols.insert("h", 5.2);
    symbols.insert("i", 5);
    symbols.insert("j", 0.8);
    symbols.insert("k", 0.7);
    symbols.insert("l", 1.02);
    symbols.insert("n", 4.3);

    symbols.print();


    senc::source_encoder* encoder = new senc::Fano_encoder(symbols);
    std::vector<std::string> codes = encoder->generate_code();

    for (int i = 0; i < codes.size(); i++)
        cout << codes[i] << endl;

    return 0;
}
