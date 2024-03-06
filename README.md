# Example: Argument Parser (C++)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Today I want to demonstrate some principles of how to parse command line arguments in ways that I personally find useful. To do so, I'll use a C++ implementation which I hastily put together.

Command line arguments allow the user to set specific parameters before launching a program. I find this approach to be especially useful if I don't have an interactive user interface available.

## Building & Running

To build the example, run:

```
make
```

To rebuild, run:

```
make rebuild
```

To remove the object files and the executable, run:

```
make clean
```

Run the example with:

```
./bin/argparser [<option> [value]]...
```

## Functionality

First, a parser object must be created:

```C++
ArgParser parser;
```

### Configuration

The parser should be configured by setting the option prefix and passing the argument data.

```C++
parser.set_prefix("--");
parser.set_args(p_argc, p_argv);
```

In this case, the prefix is set to `--`, this means that every command line option should start with `--` to be valid. If no prefix was set, the parser won't detect any options.

The argument count `p_argc` and value array `p_argv` are passed to the parser. The parser does not verify the validity of the argument data, so make sure that the count and value array actually match if you use a custom argument system. This shouldn't be a problem if you pass the `main` function's argument data.

### Command Line String

To get a string representation of the full command, use:

```C++
std::string command = parser.get_command_string();
```

This is useful for debugging, if you want to make sure that the right parameters have been set.

### Argument & Option Count

The parser can return the number of command line arguments with (this includes the name of the command):

```C++
int count = parser.get_arg_count();
```

To get the number of options (which start with the configured prefix), use:

```C++
int count = parser.get_option_count();
```

### Testing Options

There are three ways of testing options. The first approach is to test if an option with a given name exists. you can do this with:

```C++
bool hasOption = parser.has_option("name");
```

The second approach is to attempt to get an index of the option:

```C++
int index = parser.get_option_index("name");
```

The parser will either return a valid index if the option was found, or an invalid `-1` index if it wasn't found. If you want to confirm wether or not an index is valid, use:

```C++
bool isValid = parser.is_in_bounds(index);
```

### Scaning Options

If you don't want to test for specific options, but rather want to scan the arguments for option indices, use:

```C++
int index = parser.find_next_option(startIndex);
```

This either returns a valid index if any option was encountered from `startIndex` and onward, or an invalid `-1` index if none were found. Again, use the following to test wether the index is valid or not:

```C++
bool isValid = parser.is_in_bounds(index);
```

To get the name of the option at an index, use:

```C++
std::string name = parser.get_option_name(index);
```

### Getting Option Values

Options can also provide values. To test if the option has an associated value, use:

```C++
bool hasValue = parser.option_has_value(index);
```

To retrieve the value (gives an empty string if the index is invalid), use:

```C++
std::string value = parser.get_option_value(index);
```

## Conclusion

This implementation covers everything that I personally find necessary when it comes to parsing command line arguments. I think it's approach is simple and flexible, and I rarely feel the need to use a more complex approach for my projects. It might not be the most airtight solution, escpecially when it comes to the validity of the passed argument data, but that's also beyond the scope of this example.
