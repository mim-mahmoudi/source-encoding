#ifndef SOURCE_ENCODER_H
#define SOURCE_ENCODER_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

namespace senc {

//SYMBOL_LIST
class symbol_list
{
public:
    symbol_list() {}
    symbol_list(std::initializer_list<std::pair<std::string, double>>);

    void insert(std::string symbol, double weight);
    void erase(std::string symbol);
    void print();
    bool contains(std::string symbol);

    size_t size();
    double weight(std::string symbol);
    double weight(size_t index);

    std::pair<std::string, double> operator[] (size_t index);



private:
    std::vector<std::pair<std::string, double>> symbols;

    class equal_to {
        std::string& symbol;
    public:
        equal_to(std::string& s)
            :symbol(s) {}
        bool operator()(std::pair<std::string, double>& p)
        { return p.first == symbol; }
    };

    class compare {
    public:
        bool operator()(std::pair<std::string, double>& p1, std::pair<std::string, double>& p2)
        { return p1.second > p2.second; }
    };


};

//SOURCE ENCODER
class source_encoder
{
public:
    source_encoder(symbol_list& _symbols)
        :symbols{_symbols} {}

    virtual std::vector<std::string> generate_code() = 0;
protected:
    symbol_list& symbols;
    size_t n_symbols;
};

//FANO ENCODER
class Fano_encoder : public source_encoder
{
public:
    Fano_encoder(symbol_list& _symbols)
        :source_encoder(_symbols){}

    std::vector<std::string> generate_code();

private:
    void generate_fano_code(
        std::vector<std::string>& _codes,
        size_t start, size_t end, int turn = 0);

    size_t find_mid(size_t start, size_t end);
    double sum_weights(size_t start, size_t end);
};

//HAFFMAN ENCODER
class Haffman_encoder : public source_encoder
{
public:
    Haffman_encoder(symbol_list& _symbols)
        :source_encoder(_symbols) {}

    std::vector<std::string> generate_code();

};

//SHANNON ENCODER
class Shannon_encoder : public source_encoder
{
public:
    Shannon_encoder(symbol_list& _symbols)
        :source_encoder(_symbols) {}

    std::vector<std::string> generate_code();

private:
    std::string fractional_to_binary(double f, size_t len);
    double weight_sum;
};


}

#endif // SOURCE_ENCODER_H





























