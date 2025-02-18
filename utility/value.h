#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace melon
{
  namespace utility
  {
    class Value
    {
      public:
        enum ValueType
        {
          V_NULL = 0,
          V_BOOL,
          V_INT,
          V_FLOAT,
          V_DOUBLE,
          V_STRING
        };

        Value();
        Value(bool value);
        Value(int value);
        Value(unsigned int value);
        Value(float value);
        Value(double value);
        Value(const char* value);
        Value(const std::string& value);
        ~Value() = default;

        void show() const;

        Value& operator=(bool value);
        Value& operator=(int value);
        Value& operator=(unsigned int value);
        Value& operator=(float value);
        Value& operator=(double value);
        Value& operator=(const char* value);
        Value& operator=(const std::string& value);
        Value& operator=(const Value& other);

        operator bool();
        operator bool() const;
        operator int();
        operator int() const;
        operator unsigned int();
        operator unsigned int() const;
        operator float();
        operator float() const;
        operator double();
        operator double() const;
        operator std::string();
        operator std::string() const;
        
        friend std::ostream & operator << (std::ostream & os, const Value & value)
        {
          os << value.m_value;
          return os;
        }

      private:
        ValueType m_type;
        std::string m_value;
    };  
  }
}

