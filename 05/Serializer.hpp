#pragma once
#include <stdint.h>
#include <sstream>
#include <iostream>

// Ощибки
enum class Error
{
    NoError,
    CorruptedArchive
};

// Класс Серилизатора
class Serializer
{
    std::ostream& out_;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out) : out_(out){}

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT& ... args)
    {
        return process(args...);
    }

    Error process(bool &arg)
    {
        if (arg)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;
        
        return Error::NoError;
    }

    Error process(uint64_t &arg)
    {
        out_ << arg << Separator;
        return Error::NoError;
    }

private:
    template <class... ArgsT>
    Error process(bool &arg, ArgsT& ... args)
    {
        if (arg)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;

        process(args...);
        return Error::NoError;
    }

    template <class... ArgsT>
    Error process(uint64_t &arg, ArgsT& ... args)
    {
        out_ << arg << Separator;
        process(args...);
        return Error::NoError;
    }
};

// Класс Десерилизатора
class Deserializer
{
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in) : in_(in){}

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT& ... args)
    {
        return process(args...);
    }

    Error process(bool &arg)
    {
        std::string obj;
        in_ >> obj;

        if (obj == "true")
            arg = true;
        else if (obj == "false")
            arg = false;
        else
            return Error::CorruptedArchive;
        
        return Error::NoError;
    }
    
    Error process(uint64_t &arg)
    {
        std::string obj;
        in_ >> obj;

        try
        {
            arg = std::stoull(obj);
        }
        catch(std::invalid_argument const& e)
        {
            return Error::CorruptedArchive;
        }
        catch(std::out_of_range const& e)
        {
            return Error::CorruptedArchive;
        }

        return Error::NoError;
    }
private:
    
    template <class... ArgsT>
    Error process(bool &arg, ArgsT& ... args)
    {
        std::string obj;
        in_ >> obj;

        if (obj == "true")
            arg = true;
        else if (obj == "false")
            arg = false;
        else
            return Error::CorruptedArchive;
        
        return process(args...);
    }

    template <class... ArgsT>
    Error process(uint64_t &arg, ArgsT& ... args)
    {
        std::string obj;
        in_ >> obj;
        try
        {
            arg = std::stoull(obj);
        }
        catch(std::invalid_argument const& e)
        {
            return Error::CorruptedArchive;
        }
        catch(std::out_of_range const& e)
        {
            return Error::CorruptedArchive;
        }

        return process(args...);
    }
};
