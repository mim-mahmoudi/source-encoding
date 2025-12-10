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

   /* messages.insert("a", 1.2);
    messages.insert("b", 0.2);
    messages.insert("c", 3.2);
    messages.insert("d", 3.2);
    messages.insert("e", 3.2);
    messages.insert("f", 3.3);
    messages.insert("g", 1.2);
    messages.insert("h", 5.2);
    messages.insert("i", 5);
    messages.insert("j", 0.8);
    messages.insert("k", 0.7);
    messages.insert("l", 1.02);
    messages.insert("n", 4.3);*/

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 1000);

    double w;
    for (int i = 0; i < 50; i++) {
        w = (double)(distrib(gen) % 20) + 0.01 * (double)distrib(gen);
        messages.insert(std::to_string(i), w);
    }
    messages.print();


    senc::source_encoder* encoder = new senc::Fano_encoder(messages);
    std::vector<std::string> codes = encoder->generate_code();

    for (int i = 0; i < codes.size(); i++)
        cout << codes[i] << endl;

    return 0;
}
