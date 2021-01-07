# pragma once
# include "Lexical_base.hpp"

AMIC_NAMESPACE_START

class Lexical_analyzer {
public:
    token::token* get_next_token();
private:
    enum DFS_state {
        START = 0, FIRST_NUM_IN = 1, INT_WAIT_DIGIT = 2, FLT_DOT_IN = 3, FLT_WAIT_DIGIT = 4, 
        OPERATOR_IN = 5, ID_WAIT_ALPHA = 6
    } current_state = START;
    std::string origin_string;
    inline char get_next_char();

    size_t next_loca = 0;
    size_t begin_loca = 0;
    size_t last_confirmed = 0; // ¥ÌŒÛÃ· æ”√

    bool state_trans();
    inline void new_segment();

    std::stack<token::token*> all_token;
    void delete_all_token();
    void error_handle();
public:
    Lexical_analyzer(const std::string& _str);
    ~Lexical_analyzer();
    bool pre_process();
    void loca_error();
};

AMIC_NAMESPACE_END