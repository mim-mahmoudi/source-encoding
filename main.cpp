#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#include "source_encoder.h"

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

    std::cout << "messages: " << std::endl;
    messages.print();
    std::cout << "******************" << std::endl;

    int number_of_symbbols = 4;
    senc::source_encoder* encoder = new senc::Haffman_encoder(messages, number_of_symbbols);
    std::vector<std::string> codes = encoder->generate_code();

    std::cout << "codes: " << std::endl;
    for (auto& c : codes)
        std::cout << c << std::endl;

    delete encoder;
    return 0;
}








