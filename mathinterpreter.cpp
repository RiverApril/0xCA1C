#include "mathinterpreter.h"
#include <QtMath>
#include <QVector>

namespace MathInterpreter {

    SymbolExpression::~SymbolExpression(){
        delete e;
    }

    calcNumber evaluateExpression(Expression* exp){

        //Evaluate Expression: (...)
        for(int i=0;i<exp->symbols.size();i++){
            SymbolExpression* se = dynamic_cast<SymbolExpression*>(exp->symbols[i]);
            if(se){
                exp->symbols[i] = new SymbolNumber(evaluateExpression(se->e));
                delete se;
            }
        }

        for(int i=0;i<exp->symbols.size();i++){
            SymbolOperator* so = dynamic_cast<SymbolOperator*>(exp->symbols[i]);
            if(so){
                if(so->o == '-'){
                    //Evaluate Negative:  -a
                    if(i < exp->symbols.size()-1){
                        bool neg = true;
                        if(i > 0){
                            //SymbolNumber* asn = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                            SymbolOperator* aso = dynamic_cast<SymbolOperator*>(exp->symbols[i-1]);
                            neg = aso;
                        }
                        if(neg){
                            SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                            if(b){
                                exp->symbols[i] = new SymbolNumber(-(b->n));
                                delete so;
                                exp->symbols.removeAt(i+1);
                                i = 0;
                                continue;
                            }else{
                                throw SyntaxError("3 Operators in a row or 2 at begining");
                            }
                        }
                    }
                }
            }
        }

        //Evaluate Or, And, and Xor: a|b a&b a⊻b
        for(int i=0;i<exp->symbols.size();i++){
            SymbolOperator* so = dynamic_cast<SymbolOperator*>(exp->symbols[i]);
            if(so){
                if(so->o == '|'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            if((long long)(a->n) == a->n && (long long)(b->n) == b->n){
                                exp->symbols[i] = new SymbolNumber((long long)a->n | (long long)b->n);
                                delete so;
                                exp->symbols.removeAt(i+1);
                                exp->symbols.removeAt(i-1);
                                i = 0;
                                continue;
                            }else{
                                throw SyntaxError("Cannot perform bitwise operation on non whole number");
                            }
                        }else{
                            throw SyntaxError("One or both sides of | are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of | is empty");
                    }
                }else if(so->o == '&'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            if((long long)(a->n) == a->n && (long long)(b->n) == b->n){
                                exp->symbols[i] = new SymbolNumber((long long)a->n & (long long)b->n);
                                delete so;
                                exp->symbols.removeAt(i+1);
                                exp->symbols.removeAt(i-1);
                                i = 0;
                                continue;
                            }else{
                                throw SyntaxError("Cannot perform bitwise operation on non whole number");
                            }
                        }else{
                            throw SyntaxError("One or both sides of & are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of & is empty");
                    }
                }else if(so->o == 0x22BB){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            if((long long)(a->n) == a->n && (long long)(b->n) == b->n){
                                exp->symbols[i] = new SymbolNumber((long long)a->n ^ (long long)b->n);
                                delete so;
                                exp->symbols.removeAt(i+1);
                                exp->symbols.removeAt(i-1);
                                i = 0;
                                continue;
                            }else{
                                throw SyntaxError("Cannot perform bitwise operation on non whole number");
                            }
                        }else{
                            throw SyntaxError("One or both sides of ⊻ are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of ⊻ is empty");
                    }
                }else if(so->o == 0x00AB){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            if((long long)(a->n) == a->n && (long long)(b->n) == b->n){
                                exp->symbols[i] = new SymbolNumber((long long)a->n << (long long)b->n);
                                delete so;
                                exp->symbols.removeAt(i+1);
                                exp->symbols.removeAt(i-1);
                                i = 0;
                                continue;
                            }else{
                                throw SyntaxError("Cannot perform bitwise operation on non whole number");
                            }
                        }else{
                            throw SyntaxError("One or both sides of « are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of « is empty");
                    }
                }else if(so->o == 0x00BB){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            if((long long)(a->n) == a->n && (long long)(b->n) == b->n){
                                exp->symbols[i] = new SymbolNumber((long long)a->n >> (long long)b->n);
                                delete so;
                                exp->symbols.removeAt(i+1);
                                exp->symbols.removeAt(i-1);
                                i = 0;
                                continue;
                            }else{
                                throw SyntaxError("Cannot perform bitwise operation on non whole number");
                            }
                        }else{
                            throw SyntaxError("One or both sides of » are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of » is empty");
                    }
                }
            }
        }

        //Evaluate Exponent: a^b
        for(int i=0;i<exp->symbols.size();i++){
            SymbolOperator* so = dynamic_cast<SymbolOperator*>(exp->symbols[i]);
            if(so){
                if(so->o == '^'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            exp->symbols[i] = new SymbolNumber(qPow(a->n, b->n));
                            delete so;
                            exp->symbols.removeAt(i+1);
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("One or both sides of ^ are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of ^ is empty");
                    }
                }
            }
        }

        //Evaluate Multiplication, Division, and Modulo: a*b a/b a%b
        for(int i=0;i<exp->symbols.size();i++){
            SymbolOperator* so = dynamic_cast<SymbolOperator*>(exp->symbols[i]);
            if(so){
                if(so->o == '*'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            exp->symbols[i] = new SymbolNumber(a->n * b->n);
                            delete so;
                            exp->symbols.removeAt(i+1);
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("One or both sides of * are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of * is empty");
                    }
                }else if(so->o == '/'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            exp->symbols[i] = new SymbolNumber(a->n / b->n);
                            delete so;
                            exp->symbols.removeAt(i+1);
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("One or both sides of / are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of / is empty");
                    }
                }else if(so->o == '%'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            exp->symbols[i] = new SymbolNumber(fmod(a->n, b->n));
                            delete so;
                            exp->symbols.removeAt(i+1);
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("One or both sides of % are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of % is empty");
                    }
                }
            }
        }



        //Evaluate Addition and Subtraction: a+b a-b
        for(int i=0;i<exp->symbols.size();i++){
            SymbolOperator* so = dynamic_cast<SymbolOperator*>(exp->symbols[i]);
            if(so){
                if(so->o == '+'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            exp->symbols[i] = new SymbolNumber(a->n + b->n);
                            delete so;
                            exp->symbols.removeAt(i+1);
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("One or both sides of + are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of + is empty");
                    }
                }else if(so->o == '-'){
                    if(i > 0 && i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        SymbolNumber* b = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a && b){
                            exp->symbols[i] = new SymbolNumber(a->n - b->n);
                            delete so;
                            exp->symbols.removeAt(i+1);
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("One or both sides of - are Operators");
                        }
                    }else{
                        throw SyntaxError("One side of - is empty");
                    }
                }
            }
        }

        //Evaluate Multiplication: ab
        if(exp->symbols.size() > 1){
            for(int i=0;i<exp->symbols.size();i++){
                SymbolNumber* sn = dynamic_cast<SymbolNumber*>(exp->symbols[i]);
                if(sn){
                    if(i > 0){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i-1]);
                        if(a){
                            exp->symbols[i] = new SymbolNumber(a->n * sn->n);
                            delete sn;
                            exp->symbols.removeAt(i-1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("After all evals there is still a non-number during final multiplication");
                        }
                    }else if(i < exp->symbols.size()-1){
                        SymbolNumber* a = dynamic_cast<SymbolNumber*>(exp->symbols[i+1]);
                        if(a){
                            exp->symbols[i] = new SymbolNumber(a->n * sn->n);
                            delete sn;
                            exp->symbols.removeAt(i+1);
                            i = 0;
                            continue;
                        }else{
                            throw SyntaxError("After all evals there is still a non-number during final multiplication");
                        }
                    }
                }
            }
        }

        if(exp->symbols.size() > 0){
            SymbolNumber* sn = dynamic_cast<SymbolNumber*>(exp->symbols[0]);

            if(sn){
                return sn->n;
            }else{
                throw SyntaxError("After all evals there is still a non-number");
            }
        }else{
            throw SyntaxError("Empty Parenthesis");
        }
    }

    Expression* parseExpression(QString input, int base){
        int* i = new int(0);
        Expression* e = parseExpression(input, base, i);
        if(*i < input.size()){
            throw SyntaxError("Unopened Parenthesis");
        }
        return e;
    }

    Expression* parseExpression(QString input, int base, int* i){
        Expression* exp = new Expression();
        int inSize = input.size();
        QString currentNumber = "";
        QString currentFunction = "";
        for(;*i<inSize;(*i)++) {
            ushort c = input.at(*i).unicode();
            switch(c){
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                case '.':
                    if(currentFunction.size() == 0){
                        currentNumber += c;
                    }else{
                        throw SyntaxError(QString("unexpected number after function name: ")+currentFunction);
                    }
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                case '&':
                case '|':
                case 0x22BB:
                case 0x00AB://«
                case 0x00BB://»
                    if(currentFunction.size() == 0){
                        if(currentNumber.size() > 0){
                            exp->addNumber((calcNumber)QStringToNum(currentNumber, base));
                            currentNumber = "";
                        }
                        exp->addOperator(c);
                    }else{
                        throw SyntaxError(QString("unexpected number after function name: ")+currentFunction);
                    }
                    break;

                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                    if(currentFunction.size() == 0 && currentNumber.size() > 0){
                        exp->addNumber((calcNumber)QStringToNum(currentNumber, base));
                        currentNumber = "";
                    }
                    currentFunction += c;
                    break;


                case '(':
<<<<<<< HEAD
                    if(currentFunction.size() > 0){
                        exp->addfunction()
=======
                    if(currentNumber.size() > 0){
                       exp->addNumber((calcNumber)QStringToNum(currentNumber, base));
                       currentNumber = "";
                       //exp->addOperator('*');
                    }
                    if(*i < inSize - 1){
                        (*i)++;
                        exp->addExpression(parseExpression(input, base, i));
>>>>>>> 485036b06320e83dbe91579531e00a188a8e8119
                    }else{
                        if(currentNumber.size() > 0){
                           exp->addNumber((calcNumber)QStringToNum(currentNumber, base));
                           currentNumber = "";
                           exp->addOperator('*');
                        }
                        if(*i < inSize - 1){
                            (*i)++;
                            exp->addExpression(parseExpression(input, base, i));
                        }else{
                            throw SyntaxError("Unclosed Parenthesis");
                        }
                    }
                    break;

                case ')':
                    if(currentNumber.size() > 0){
                       exp->addNumber((calcNumber)QStringToNum(currentNumber, base));
                       currentNumber = "";
                    }
                    return exp;

                default:
                    throw SyntaxError("Symbol can not be evaluated: \'"+QString(QChar(c))+"\'");

            }
        }
        if(currentNumber.size() > 0){
            exp->addNumber((calcNumber)QStringToNum(currentNumber, base));
        }
        return exp;
    }

    QString interpretToString(QString input, int base){
        if(input.length() == 0){
            return "";
        }
        Expression* parsed = NULL;
        try{
            parsed = parseExpression(input, base);
            calcNumber evaluated = 0;
            evaluated = evaluateExpression(parsed);
            delete parsed;
            return numToQString(evaluated, base);
        }catch(SyntaxError e){
            if(parsed){
                delete parsed;
            }
            throw FailedInterpret("Syntax Error: "+e.message);
        }
    }

    long double interpretToNumber(QString input, int base){
        if(input.length() == 0){
            return 0;
        }
        Expression* parsed = NULL;
        try{
            parsed = parseExpression(input, base);
            calcNumber evaluated = 0;
            evaluated = evaluateExpression(parsed);
            delete parsed;
            return evaluated;
        }catch(SyntaxError e){
            if(parsed){
                delete parsed;
            }
            throw FailedInterpret("Syntax Error: "+e.message);
        }
    }

    int getNumberFromSymbol(char symbol){
        if (symbol >= 48 && symbol <= 57) { // 0 - 9
            return symbol - 48;
        } else if (symbol >= 65 && symbol <= 90) { // A - Z
            return symbol - 65 + 10;
        } else if (symbol >= 97 && symbol <= 122) { // a - z
            return symbol - 97 + 10;
        } else {
            throw SyntaxError(QString("Unknown symbol as number: ")+symbol);
        }
    }

    char getSymbolFromNumber(int number){
        if(number >= 0 && number <= 9){
            return (char)(number + 48);
        }else if(number >= 10 && number < 10 + 26){
            return (char)(number - 10 + 65);
        }
        throw SyntaxError(QString("Digit too big or small: ")+number);
    }

    long double QStringToNum(QString s, int base){
        if (base < 1 || base > 36) {
            throw SyntaxError(QString("Base is out of range: ")+base);
        } else {
            bool addToLeft = true;
            bool negative = false;
            QVector<int> left;
            QVector<int> right;
            int i = 0;
            if (s[0] == '-') {
                negative = true;
                i=1;
            }
            for (; i < s.length(); i++) {
                if (s[i] == '.') {
                    if (addToLeft) {
                        addToLeft = false;
                    } else {
                        throw SyntaxError("Too many decimal places");
                    }
                } else {
                    int n = getNumberFromSymbol(s[i].toLatin1());
                    if (n >= base) {
                        throw SyntaxError("Digit is larger than base");
                    } else {
                        if (addToLeft) {
                            left.push_back(n);
                        } else {
                            right.push_back(n);
                        }
                    }
                }
            }
            long double final = 0;
            int d = 0;
            for (int i = (int) left.size() - 1; i >= 0; i--) {
                final += qPow(base, d) * left[i];
                d++;
            }

            d = -1;

            for (int i = 0; i < right.size(); i++) {
                final += qPow(base, d) * right[i];
                d--;
            }

            if(negative){
                final = -final;
            }

            return final;
        }
    }

    QString numToQString(long double num, int base){
        if(base < 1 || base > 62){
            throw SyntaxError(QString("Base is out of range: ")+base);
        }else{
            bool negative = false;
            if(num < 0){
                negative = true;
                num = -num;
            }

            QVector<int> digitListLeft;
            QVector<int> digitListRight;
            int digitPos = 0;
            for(int i=maxDigit;i>=0;i--){
                long double digit = qPow(base, i);
                digitListLeft.push_back(0);
                while(num >= digit){
                    num -= digit;
                    digitListLeft[digitPos] ++;
                }
                digitPos++;
            }
            digitPos = 0;
            for(int i=-1;i>=minDigit;i--){
                long double digit = qPow(base, i);
                digitListRight.push_back(0);
                while(num >= digit){
                    num -= digit;
                    digitListRight[digitPos] ++;
                }
                digitPos++;
            }

            QString final = "";

            bool onlyZeros = true;

            for(int digit : digitListLeft){
                char sy = getSymbolFromNumber(digit);
                if(onlyZeros && sy != '0'){
                    onlyZeros = false;
                }
                if(!onlyZeros){
                    final += sy;
                }
            }

            if(digitListRight.size() > 0){

                QString temp = "";

                onlyZeros = true;

                for(int i=digitListRight.size()-1;i>=0;i--){
                    char sy = getSymbolFromNumber(digitListRight[i]);
                    if(onlyZeros && sy != '0'){
                        onlyZeros = false;
                    }
                    if(!onlyZeros){
                        temp = sy+temp;
                    }
                }


                if(!onlyZeros){
                    temp = '.'+temp;
                }

                final = final+temp;
            }

            if(negative){
                final = '-'+final;
            }

            return final;
        }
    }

}
