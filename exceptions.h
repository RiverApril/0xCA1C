#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <QApplication>

struct SyntaxError{
    SyntaxError(QString m){
        message = m;
    }
    QString message;
};

struct FailedInterpret{
    FailedInterpret(QString m){
        message = m;
    }
    QString message;
};

#endif // EXCEPTIONS

