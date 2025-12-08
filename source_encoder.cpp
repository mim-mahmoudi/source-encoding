#include "source_encoder.h"

namespace senc {

//SYMBOL_LIST
symbol_list::symbol_list(std::initializer_list<std::pair<std::string, double>> list)
    :symbols{list} {
    std::sort(symbols.begin(), symbols.end(), compare());
}

void symbol_list::insert(std::string symbol, double weight) {
    if (weight <= 0.0)
        std::abort();
    if (symbol.empty())
        std::abort();

    auto it = std::find_if(symbols.begin(), symbols.end(), equal_to(symbol));

    if (it == symbols.end()) {
        symbols.push_back({symbol, weight});
        std::sort(symbols.begin(), symbols.end(), compare());
    }
    else {
        it->second = weight;
    }
}

void symbol_list::erase(std::string symbol) {
    auto it = std::find_if(symbols.begin(), symbols.end(), equal_to(symbol));
    symbols.erase(it);
    std::sort(symbols.begin(), symbols.end(), compare());
}

void symbol_list::print() {
    std::for_each(symbols.begin(), symbols.end(),
        [](std::pair<std::string, double>& sym)
        { std::cout << sym.first << "\t" << sym.second << std::endl;});
}

bool symbol_list::contains(std::string symbol) {
    return symbols.end() != std::find_if(symbols.begin(), symbols.end(), equal_to(symbol));
}

size_t symbol_list::size() {
    return symbols.size();
}

double symbol_list::weight(std::string symbol) {
    auto it = std::find_if(symbols.begin(), symbols.end(), equal_to(symbol));
    if (it == symbols.end())
        return 0.0;
    else
        return it->second;
}

double symbol_list::weight(size_t index) {
    if ((index < 0) || (index >= symbols.size()))
        return 0.0;
    return symbols[index].second;
}

std::pair<std::string, double> symbol_list::operator[] (size_t index) {
    if ((index < 0) || (index >= symbols.size()))
        return {};
    return symbols[index];
}

//FANO ENCODER
std::vector<std::string> Fano_encoder::generate_code() {
    n_symbols = symbols.size();
    if (n_symbols == 0)
        return {};

    std::vector<std::string> codes(n_symbols, "");
    generate_fano_code(codes, 0, n_symbols - 1, 0);
    return codes;
}

void Fano_encoder::generate_fano_code(
    std::vector<std::string>& _codes,
    size_t start, size_t end, int turn) {

    if (end < start)
        return;
    size_t len = end - start + 1;
    size_t mid = find_mid(start, end);
    size_t i = 0;

    switch(turn) {
    case 0:
        generate_fano_code(_codes, start, mid, -1);
        generate_fano_code(_codes, mid+1, end, +1);
        break;

    case -1:
        if (len == 1) {
            _codes[start] += "0";
            return;
        }
        else {
            for (i = start; i <= end; i++) {
                _codes[i] += "0";
            }
            generate_fano_code(_codes, start, mid, -1);
            generate_fano_code(_codes, mid+1, end, +1);
        }
        break;

    case +1:
        if (len == 1) {
            _codes[start] += "1";
            return;
        }
        else {
            for (i = start; i <= end; i++) {
                _codes[i] += "1";
            }
            generate_fano_code(_codes, start, mid, -1);
            generate_fano_code(_codes, mid+1, end, +1);
        }
        break;
    }
    return;
}

size_t Fano_encoder::find_mid(size_t start, size_t end) {
    if (end <= start + 1)
        return start;

    size_t i;
    double pmin = 0.0;
    double nextpmin = std::min(sum_weights(start, start), sum_weights(start + 1, end));

    for (i = start; i < end - 1; i++) {
        pmin = nextpmin;
        nextpmin = std::min(sum_weights(start, i + 1), sum_weights(i + 2, end));

        if (pmin > nextpmin) {
            return i;
        }
    }
    return end - 1;
}

double Fano_encoder::sum_weights(size_t start, size_t end) {
    double sum = 0.0;
    size_t i;
    for (i = start; i <= end; i++)
        sum += symbols.weight(i);
    return sum;
}

//HAFFMAN ENCODER
std::vector<std::string> Haffman_encoder::generate_code() {
    n_symbols = symbols.size();
    if (n_symbols == 0)
        return {};

    std::vector<std::string> codes(n_symbols, "");





}

//SHANNON ENCODER
std::vector<std::string> Shannon_encoder::generate_code() {

}

std::string Shannon_encoder::fractional_to_binary(double f, size_t len) {

}





}



















