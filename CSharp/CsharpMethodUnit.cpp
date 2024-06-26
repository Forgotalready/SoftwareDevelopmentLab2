#include "CsharpMethodUnit.h"

CsharpMethodUnit::CsharpMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    :AbstractMethodUnit(name, returnType, flags){}

void CsharpMethodUnit::add(const std::shared_ptr<Unit> &unit, Flags)
{
    m_body.push_back(unit);
}

std::string CsharpMethodUnit::compile(unsigned int level) const
{
    std::string result = generateShift(level);
    if(m_flags & STATIC){
        result += "static ";
    }else if(m_flags & VIRTUAL){
        result += "virtual ";
    }
    result += m_returnType + " ";
    result += m_name + " () ";
    if(m_flags & CONST){
        qWarning("C# does not support const methods");
    }
    result += " {\n";
    for(const auto& b : m_body){
        result += b->compile(level + 1);
    }
    result += generateShift(level) + "}\n";
    return result;
}
