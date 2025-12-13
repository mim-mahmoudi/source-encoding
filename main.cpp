#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#include "source_encoder.h"

using namespace std;

int main()
{
    senc::message_ensemble messages;
    messages.insert("a", 0.22);
    messages.insert("b", 0.20);
    messages.insert("c", 0.18);
    messages.insert("d", 0.15);
    messages.insert("e", 0.10);
    messages.insert("f", 0.08);
    messages.insert("g", 0.05);
    messages.insert("h", 0.02);

    std::cout << "messages: " << endl;
    messages.print();
    std::cout << "******************" << endl;

    senc::source_encoder* encoder = new senc::Haffman_encoder(messages, 4);
    std::vector<std::string> codes = encoder->generate_code();

    std::cout << "codes: " << endl;
    for (int i = 0; i < codes.size(); i++)
        cout << codes[i] << endl;

    delete encoder;
    return 0;
}








