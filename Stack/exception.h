#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
class RuntimeException
{
private:
    std::string message;

public:
    RuntimeException(std::string s) : message(s) {}
    void getMes()
    {
        std::cout << message << std::endl;
    }
};
class StackEmpty : public RuntimeException
{
public:
    StackEmpty(std::string s) : RuntimeException(s) {}
};
class StackFull : public RuntimeException
{
public:
    StackFull(std::string s) : RuntimeException(s) {}
};
#endif