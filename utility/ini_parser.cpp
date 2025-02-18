#include "utility/ini_parser.h"

using namespace melon::utility;

typedef std::map<std::string, Value> Section;

IniParser::IniParser(const std::string& filename)
{
  load(filename);
}

std::string IniParser::trim(std::string s)
{
  if (s.empty()) return s;
  s.erase(0, s.find_first_not_of(" \n\r"));
  s.erase(s.find_last_not_of(" \n\r") + 1);
  return s;
}

bool IniParser::load(const std::string& filename)
{
  m_sections.clear();
  m_filename = filename;

  std::ifstream fin(filename);
  if (fin.fail())
    throw std::logic_error("loading ini file failed: " + filename);

  std::string line;
  std::string section;
  while (std::getline(fin, line))
  {
    line = trim(line);
    if (line.empty())
      continue;
    if (line[0] == '#' || line[0] == ';')
      continue;
    if (line[0] == '[')
    {
      std::size_t pos = line.find_first_of(']');
      if (pos == std::string::npos)
        throw std::logic_error("Invalid section: " + line);
      section = line.substr(1, pos - 1);
      section = trim(section);
      m_sections[section] = Section();
    }
    else
    {
      std::size_t pos = line.find_first_of('=');
      if (pos == std::string::npos)
        throw std::logic_error("Invalid option: " + line);
      std::string key = trim(line.substr(0, pos));
      std::string value = trim(line.substr(pos + 1));
      m_sections[section][key] = value;
    }
  }

  fin.close();
  return true;
}

std::string IniParser::str() const
{
  std::stringstream ss;
  for (const auto& section : m_sections)
  {
    ss << '[' << section.first << ']' << '\n';
    for (const auto& option : section.second)
    {
      ss << option.first << " = " << (std::string)(option.second) << '\n';
    }
    ss << '\n';
  }
  return ss.str();
}

void IniParser::show() const
{
  std::cout << str();
}

bool IniParser::has(const std::string& section)
{
  return m_sections.find(section) != m_sections.end();
}

bool IniParser::has(const std::string& section, const std::string& key)
{
  return m_sections.find(section) != m_sections.end()
      && m_sections[section].find(key) != m_sections[section].end();
}

Value& IniParser::get(const std::string& section, const std::string& key)
{
  if (!has(section, key))
    throw std::logic_error("Section or key isn't exist.");
  return m_sections[section][key]; 
}

void IniParser::set(const std::string& section, const std::string& key, const Value& value)
{
  m_sections[section][key] = value;
}

Section& IniParser::operator[](const std::string& section)
{
  return m_sections[section];
}

      
void IniParser::remove(const std::string& section)
{
  m_sections.erase(section);
}

void IniParser::remove(const std::string& section, const std::string& key)
{
  auto it = m_sections.find(section);
  if (it != m_sections.end())
    it->second.erase(key);
}

void IniParser::clear()
{
  m_sections.clear();
}

void IniParser::save(const std::string& filename)
{
  std::ofstream fout(filename);
  if (fout.fail())
    throw std::logic_error("Open ini file failed: " + filename);
  
  fout << str();
    
  fout.close();
}

