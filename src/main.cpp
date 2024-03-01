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

// C++ headers:
#include <iostream>

// Example headers:
#include <example/arg-parser.hpp>

int main(int p_argc, char **p_argv)
{
  ArgParser parser;

  parser.set_prefix("--");
  parser.set_args(p_argc, p_argv);

  std::cout << "Command string: " << parser.get_command_string() << "\n";
  std::cout << "Number of arguments: " << parser.get_arg_count() << "\n";
  std::cout << "Number of options: " << parser.get_option_count() << std::endl;

  int i;

  // List the options.
  for (i = 0; parser.is_in_bounds(i); i++)
  {
    i = parser.find_next_option(i);

    // End of list reached.
    if (i == -1)
    {
      break;
    }

    std::cout << "Option: " << parser.get_option_name(i);

    if (parser.option_has_value(i))
    {
      std::cout << " => " << parser.get_option_value(i) << std::endl;
    }
    else
    {
      std::cout << std::endl;
    }
  }

  // Triggered by the magic option.
  if (parser.has_option("magic"))
  {
    std::cout << "Magic option detected at index: " << parser.get_option_index("magic") << std::endl;
  }

  return 0;
}