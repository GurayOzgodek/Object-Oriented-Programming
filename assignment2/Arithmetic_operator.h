#ifndef Arithmetic_operator_h
#define Arithmetic_operator_h
#include "Operator.h"

class ArithmeticOperator: public Operator{
    char sign;
    public:
        ArithmeticOperator(int x, int y, int size, char sign);
        char get_sign();
        void print_operator();

};
ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign):Operator(x, y, size){
    if(sign != '+' && sign != '-' && sign!= 'x' && sign != '/'){
        std::cout << "SIGN parameter is invalid!" << endl;
    }
    else this->sign = sign;
}
char ArithmeticOperator::get_sign(){return sign; }
#endif