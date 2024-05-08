#include <QCoreApplication>

#include <iostream>
#include "Abstract/AbstractCodeFactory.h"
#include "cpp/CppCodeFactory.h"

std::string generateProgram(std::shared_ptr<AbstractCodeFactory>& factory){
    using std::shared_ptr;

    shared_ptr<AbstractClassUnit> myClass = factory->createClass("MyClass");
    myClass->add(
        factory->createMethod("testFunc1", "void", 0),
        AbstractClassUnit::PUBLIC
    );
    myClass->add(
        factory->createMethod("testFunc3", "void", AbstractMethodUnit::STATIC),
        AbstractClassUnit::PRIVATE
    );
    myClass->add(
        factory->createMethod(
            "testFunc3",
            "void",
            AbstractMethodUnit::VIRTUAL | AbstractMethodUnit::CONST
        ),
        AbstractClassUnit::PUBLIC
    );
    auto method = factory->createMethod( "testFunc4", "void", AbstractMethodUnit::STATIC );
    method->add(factory->createPrintMethod( R"(Hello, world!\n)" ) );
    myClass->add( method, AbstractClassUnit::PROTECTED );
    return myClass->compile();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<AbstractCodeFactory> factory = std::make_shared<CppCodeFactory>();
    std::cout << generateProgram(factory) << std::endl;

    return a.exec();
}
