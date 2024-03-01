/*
MIT License

Copyright (c) 2024 Diordany van Hemert

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// C headers:
#include <cstring>

// Example headers:
#include <example/arg-parser.hpp>

int ArgParser::find_next_option(int p_startIndex)
{
  int i;

  // Search for the next option and return its index if found.
  for (i = p_startIndex; i < this->argc; i++)
  {
    if (this->has_option_at_index(i))
    {
      return i;
    }
  }

  // No option was found.
  return -1;
}

int ArgParser::get_arg_count(void)
{
  return this->argc;
}

std::string ArgParser::get_command_string(void)
{
  // Add the invoked command to the string.
  std::string cmdStr = std::string(this->argv[0]);

  int i;

  // Add the arguments to the string.
  for (i = 1; i < this->argc; i++)
  {
    // Wrap in quotation marks if the argument contains spaces.
    if (std::strchr(this->argv[i], ' '))
    {
      cmdStr += " \"" + std::string(this->argv[i]) + '"';
    }
    else
    {
      cmdStr += " " + std::string(this->argv[i]);
    }
  }

  return cmdStr;
}

int ArgParser::get_option_count(void)
{
  int count = 0;
  int i;

  // Search for options.
  for (i = 0; i < this->argc; i++)
  {
    if (this->has_option_at_index(i))
    {
      count++;
    }
  }

  return count;
}

int ArgParser::get_option_index(std::string p_name)
{
  int i;

  // Search an option with the given name.
  for (i = 0; i < this->argc; i++)
  {
    if (this->get_option_name(i) == p_name)
    {
      return i;
    }
  }

  // Not found.
  return -1;
}

std::string ArgParser::get_option_name(int p_index)
{
  // Return an empty string if there's no option at the given index.
  if (!this->has_option_at_index(p_index))
  {
    return "";
  }

  return std::string(this->argv[p_index]).substr(this->prefix.length());
}

std::string ArgParser::get_option_value(int p_index)
{
  // Return an empty string if the next index is out of bounds.
  if (!this->is_in_bounds(p_index + 1))
  {
    return "";
  }

  return std::string(this->argv[p_index + 1]);
}

bool ArgParser::has_option(std::string p_name)
{
  int i;

  // Search an option with the given name.
  for (i = 0; i < this->argc; i++)
  {
    if (this->get_option_name(i) == p_name)
    {
      return true;
    }
  }

  // Not found.
  return false;
}

bool ArgParser::has_option_at_index(int p_index)
{
  // Return false if the index is out of bounds or if no option prefix was set.
  if (!this->is_in_bounds(p_index) || this->prefix.length() < 1)
  {
    return false;
  }

  // Test if the string starts with, and does not consist only of the prefix.
  return std::strncmp(this->argv[p_index], this->prefix.c_str(), this->prefix.length()) == 0 &&
      strlen(this->argv[p_index]) > this->prefix.length();
}

bool ArgParser::is_in_bounds(int p_index)
{
  return p_index >= 0 && p_index < this->argc;
}

bool ArgParser::option_has_value(int p_index)
{
  // Make sure the index of the next argument is within bounds.
  if (!this->is_in_bounds(p_index + 1))
  {
    return false;
  }

  // The next argument should not be an option.
  return !this->has_option_at_index(p_index + 1);
}

void ArgParser::set_args(int p_argc, char **p_argv)
{
  this->argc = p_argc;
  this->argv = p_argv;
}

void ArgParser::set_prefix(std::string p_prefix)
{
  this->prefix = p_prefix;
}