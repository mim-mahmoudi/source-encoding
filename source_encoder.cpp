#include "source_encoder.h"

namespace senc {

//message_ensemble
message_ensemble::message_ensemble(std::initializer_list<std::pair<std::string, double>> list)
    :messages{list} {
    std::sort(messages.begin(), messages.end(), compare());
}

void message_ensemble::insert(std::string message, double weight) {
    if (weight <= 0.0)
        std::abort();
    if (message.empty())
        std::abort();

    auto it = std::find_if(messages.begin(), messages.end(), equal_to(message));

    if (it == messages.end()) {
        messages.push_back({message, weight});
        std::sort(messages.begin(), messages.end(), compare());
    }
    else {
        it->second = weight;
    }
}

void message_ensemble::erase(std::string message) {
    auto it = std::find_if(messages.begin(), messages.end(), equal_to(message));
    messages.erase(it);
    std::sort(messages.begin(), messages.end(), compare());
}

void message_ensemble::print() {
    std::for_each(messages.begin(), messages.end(),
        [](std::pair<std::string, double>& msg)
        { std::cout << msg.first << "\t" << msg.second << std::endl;});
}

bool message_ensemble::contains(std::string message) {
    return messages.end() != std::find_if(messages.begin(), messages.end(), equal_to(message));
}

size_t message_ensemble::size() {
    return messages.size();
}

double message_ensemble::weight(std::string message) {
    auto it = std::find_if(messages.begin(), messages.end(), equal_to(message));
    if (it == messages.end())
        return 0.0;
    else
        return it->second;
}

double message_ensemble::weight(size_t index) {
    if ((index < 0) || (index >= messages.size()))
        return 0.0;
    return messages[index].second;
}

double message_ensemble::frequecny(std::string message) {
    auto it = std::find_if(messages.begin(), messages.end(), equal_to(message));
    if (it == messages.end())
        return 0.0;
    else
        return (it->second) / sum_of_weights();
}

double message_ensemble::frequecny(size_t index) {
    if ((index < 0) || (index >= messages.size()))
        return 0.0;
    return messages[index].second / sum_of_weights();
}

std::pair<std::string, double> message_ensemble::operator[] (size_t index) {
    if ((index < 0) || (index >= messages.size()))
        return {};
    return messages[index];
}

//SOURCE ENCODER
source_encoder::source_encoder(message_ensemble& _messages, size_t _n_syms)
    :messages{_messages} {
    set_num_symbols(_n_syms);
}

std::vector<std::string> source_encoder::generate_code() {
    n_messages = messages.size();
    if (n_messages == 0)
        return {};
    else if (n_messages == 1)
        return {{"0"}};

    std::vector<std::string> codes(n_messages, "");
    encoder(codes);
    return codes;
}

void source_encoder::set_num_symbols(size_t _n_syms) {
    if (_n_syms < 2)
        std::abort();
    n_symbols = _n_syms;
}

//FANO ENCODER
Fano_encoder::Fano_encoder(message_ensemble& _messages, size_t _n_syms)
    :source_encoder(_messages, _n_syms) {}

void Fano_encoder::encoder(std::vector<std::string>& _codes) {
    generate_fano_code(_codes, 0, n_messages - 1, 0);
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
        sum += messages.weight(i);
    return sum;
}

//HAFFMAN ENCODER
Haffman_encoder::Haffman_encoder(message_ensemble& _messages, size_t _n_syms)
    :source_encoder(_messages, _n_syms) {
}

void Haffman_encoder::encoder(std::vector<std::string>& _codes) {
    generate_haffman_code(_codes);
}

void Haffman_encoder::generate_haffman_code(
        std::vector<std::string>& _codes) {
    size_t n0 = n_messages % (n_symbols - 1);
    size_t n_stages = (n_messages - n0) / (n_symbols - 1);
    std::vector<size_t> places(n_stages);

    size_t i, j = 0.0;

    double sum;

    for (i = 0; i < n_stages; i++) {
        size_t end;
        sum = 0.0;

        switch(i) {
        case 0:
            end = n_messages;
        default:
            end = (n_stages - i) * n_symbols;
        };

        for (j = (n_stages - i) * (n_symbols - 1); j < end; j++) {
            sum += messages.weight(j);
        }

        for (j = 0; j < end; j++) {
            /*if (sum > messages.weight(j);) {
                //places[i] = j;
            }*/
        }
    }

    fill(_codes, places);

    // _codes.reverse();
    for (i = 0; i < n_messages; i++)
    {
        std::reverse(_codes[i].begin(), _codes[i].end());
    }
}

void Haffman_encoder::fill(std::vector<std::string>& _codes,
        std::vector<size_t>& _places, size_t stage) {


}

//SHANNON ENCODER
Shannon_encoder::Shannon_encoder(message_ensemble& _messages, size_t _n_syms)
    :source_encoder(_messages, _n_syms) {
}

void Shannon_encoder::encoder(std::vector<std::string>& _codes) {
    generate_shannon_code(_codes);
}

void Shannon_encoder::generate_shannon_code(
    std::vector<std::string>& _codes) {
    size_t precision;
    double commulative_p = 0.0;

    _codes[0] = base_n(0.0, n_symbols, std::ceil(-std::log2(messages.frequecny(0)))).second;
    int i;
    for (i = 1; i < n_messages; i++) {
        precision = (size_t) std::ceil(-std::log2(messages.frequecny(i)));
        commulative_p += messages.frequecny(i - 1);
        _codes[i] = base_n(commulative_p, n_symbols, precision).second;
    }
}

std::pair<std::string,std::string> Shannon_encoder::base_n(double f, int base, size_t precision) {
    if ((precision < 0) || (base < 2))
        std::abort();

    double g = std::abs(f);
    int integer_part = (int)g ;
    double fractional_part = g - (double)integer_part;

    std::pair<std::string,std::string> base_n{"", ""};
    int nit = 0;

    //integer part
    while (integer_part != 0) {
        nit  = integer_part % base;
        base_n.first.append(std::to_string(nit));

        integer_part -= nit;
        integer_part /= base;
    }
    std::reverse(base_n.first.begin(), base_n.first.end());

    //fractional part
    int i, j;
    double tmp;
    for (i = 0; i < precision; i++) {
        for (j = 1; j <= base; j++) {
            tmp = fractional_part + (double) j / base;
            if (tmp >= 1) {
                base_n.second.append(std::to_string(base - j));
                fractional_part = tmp - 1.0;
                fractional_part *= base;
                break;
            }
        }
    }

    return base_n;
}
} //namespace senc



















