enum TokenType {NUM_DEC, NUM_INT, ID, TEXT};

template <typename T>

class Tokens {
    
    TokenType type;
    T value;


    public:
    
    Tokens(TokenType type, T value) {
        this->type = type;
        this->value = value;
    }

}

