#ifndef SOURCE_ENCODER_H
#define SOURCE_ENCODER_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

namespace senc {

//MESSAGE_ENSEMBLE
class message_ensemble
{
public:
    message_ensemble() {}
    message_ensemble(std::initializer_list<std::pair<std::string, double>> list);
    message_ensemble(std::vector<std::pair<std::string, double>> list);

    void insert(std::vector<std::pair<std::string, double>> list);
    void insert(std::string message, double weight);
    void erase(std::string message);
    void print();
    bool contains(std::string message);

    size_t size();
    double weight(std::string message);
    double weight(size_t index);
    double entropy() { return 2; }

    std::pair<std::string, double> operator[] (size_t index);

private:
    std::vector<std::pair<std::string, double>> messages;

    class equal_to {
        std::string& message;
    public:
        equal_to(std::string& s)
            :message(s) {}
        bool operator()(std::pair<std::string, double>& p)
        { return p.first == message; }
    };

    class compare {
    public:
        bool operator()(std::pair<std::string, double>& p1, std::pair<std::string, double>& p2)
        { return p1.second > p2.second; }
    };
};


//ALPHABET
class alphabet
{

};

// CODE
class code
{
public:
    code(size_t _n_syms);
    virtual void push_back(int symbol) = 0;

private:
    //std::string c;
    size_t n_symbols;

};

class string_code: public code
{

};

// CODE ENSEMBLE
class code_ensemble
{
public:
    code_ensemble(size_t _n_msgs, size_t _n_syms = 2);
    void insert();
    void reverse();

private:
    std::vector<std::string> codes;
};

//SOURCE ENCODER
class source_encoder
{
public:
    source_encoder(message_ensemble& _messages, size_t _n_syms = 2);
    std::vector<std::string> generate_code();
    void set_num_symbols(size_t d);
protected:
    virtual void encoder(std::vector<std::string>& _codes) = 0;
    message_ensemble& messages;
    size_t n_messages;
    size_t n_symbols;
};

//FANO ENCODER
class Fano_encoder : public source_encoder
{
public:
    Fano_encoder(message_ensemble& _messages, size_t _n_syms = 2);

private:
    void encoder(std::vector<std::string>& _codes);
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
    Haffman_encoder(message_ensemble& _messages, size_t _n_syms = 2);
private:
    void encoder(std::vector<std::string>& _codes);
    void generate_haffman_code(
        std::vector<std::string>& _codes);
    void fill(std::vector<std::string>& _codes,
        std::vector<size_t>& _places, size_t stage = 0);


};

//SHANNON ENCODER
class Shannon_encoder : public source_encoder
{
public:
    Shannon_encoder(message_ensemble& _messages, size_t _n_syms = 2);

private:
    void encoder(std::vector<std::string>& _codes);
    void generate_shannon_code(std::vector<std::string>& _codes);
    std::vector<int> base_n(double f, int base,  size_t len);
};
}

#endif // SOURCE_ENCODER_H





























