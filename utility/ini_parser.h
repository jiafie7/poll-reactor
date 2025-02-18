#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <sstream>
#include <string>
#include "utility/value.h"

namespace melon
{
  namespace utility
  {
    class IniParser
    {
      typedef std::map<std::string, Value> Section;
      public:
        IniParser() = default;
        IniParser(const std::string& filename);
        ~IniParser() = default;
        
        bool load(const std::string& filename);

        std::string str() const;
        void show() const;

        bool has(const std::string& section);
        bool has(const std::string& section, const std::string& key);
        Value& get(const std::string& section, const std::string& key);
        void set(const std::string& section, const std::string& key, const Value& value);

        Section& operator[](const std::string& section);

        void remove(const std::string& section);
        void remove(const std::string& section, const std::string& key);

        void clear();

        void save(const std::string& filename);


      private:
        std::string trim(std::string s);

      private:
        std::string m_filename;
        std::map<std::string, Section> m_sections;
    };
  }
}

