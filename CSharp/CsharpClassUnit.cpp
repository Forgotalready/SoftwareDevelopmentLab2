#include "CsharpClassUnit.h"

const std::vector<std::string> CsharpClassUnit::ACCESS_MODIFIERS = {"public", "protected", "private", "private protected", "file", "internal", "protected internal"};

CsharpClassUnit::CsharpClassUnit(const std::string &name)
    :AbstractClassUnit(name)
{
    m_fields.resize(ACCESS_MODIFIERS.size());
}

void CsharpClassUnit::add(const std::shared_ptr<Unit> &unit, Flags flags)
{
    int accessModifier = PRIVATE;
    if(flags < ACCESS_MODIFIERS.size()){
        accessModifier = flags;
    }else{
        qWarning("C# does not support this modifier");
    }

    m_fields[accessModifier].push_back(unit);
}

std::string CsharpClassUnit::compile(unsigned int level) const
{
    std::string result = generateShift(level) + "class " + m_name + " {\n";
    for(size_t i = 0;i < ACCESS_MODIFIERS.size();++i){
        if(m_fields[i].empty()){
            continue;
        }
        for(const auto& f : m_fields[i]){
            result += (ACCESS_MODIFIERS[i] + " ");
            result += f->compile(level);
        }
        result += "\n";
    }
    result += generateShift(level) + "}\n";
    return result;
}
