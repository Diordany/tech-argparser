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

#ifndef NANOARG_ARG_PARSER_HPP
#define NANOARG_ARG_PARSER_HPP

// C++ headers:
#include <iostream>
#include <string>

class ArgParser
{
private:
  std::string prefix = "";

  int argc = 0;
  char **argv = nullptr;
public:
  int find_next_option(int p_startIndex);
  int get_arg_count(void);
  std::string get_command_string(void);
  int get_option_count(void);
  int get_option_index(std::string p_name);
  std::string get_option_name(int p_index);
  std::string get_option_value(int p_index);
  bool has_option(std::string p_name);
  bool has_option_at_index(int p_index);
  bool is_in_bounds(int p_index);
  bool option_has_value(int p_index);
  void set_args(int p_argc, char **p_argv);
  void set_prefix(std::string p_prefix);
};

#endif