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
class QueueEmpty : public RuntimeException
{
public:
    QueueEmpty(std::string s) : RuntimeException(s) {}
};
class QueueFull : public RuntimeException
{
public:
    QueueFull(std::string s) : RuntimeException(s) {}
};
#endif