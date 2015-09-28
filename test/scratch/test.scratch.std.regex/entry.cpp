/* /////////////////////////////////////////////////////////////////////////
 * File:        entry.cpp
 *
 * Purpose:     Entry-point implementation file for the mtgrep project.
 *
 * Created:     28th September 2015
 * Updated:     28th September 2015
 *
 * www:         http://www.synesis.com.au/
 *
 * Copyright (c) 2015, Synesis Software Pty Ltd.
 * All rights reserved.
 *
 * The source code contained herein is subject to the accompanying license,
 * https://github.com/synesissoftware/mtgrep/blob/master/LICENSE, which is
 * an unmodifed form of the 4-clause BSD license.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * preprocessor control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* Pantheios header files - 1 */
#include <pantheios/pan.hpp>

/* libCLImate header files */
#include <libclimate/main.hpp>

/* CLASP header files */
#include <systemtools/clasp/clasp.hpp>

/* FastFormat header files */
#include <fastformat/ff.hpp>
#include <fastformat/sinks/ostream.hpp>

/* Pantheios header files - 2 */

/* STLSoft header files */
#include <stlsoft/filesystem/read_line.hpp>

/* Standard C++ header files */
#include <iostream>
#include <regex>

/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

static int const          verMajor    = 0;
static int const          verMinor    = 0;
static int const          verRevision = 7;

static char const* const  ToolName    = "mtgrep";
static char const* const  Summary     = "Simple grep program";
static char const* const  Copyright   = "Copyright (c) Synesis Software Pty Ltd";
static char const* const  Description = "simple grep test program";
static char const* const  Usage       = "mtgrep { --help | --version | <pattern>}";

/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

extern "C"
clasp::alias_t const libCLImate_aliases[] =
{
  // standard flags

  CLASP_GAP_SECTION("Standard Flags:"),

  CLASP_FLAG( NULL,   "--help", "displays this help and exits"),
  CLASP_FLAG( NULL,   "--version", "displays version information and exits"),


  // program logic

  CLASP_GAP_SECTION("Matching Control:"),

};

/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static void show_usage(clasp_arguments_t const* args);
static void show_version(clasp_arguments_t const* args);

/* /////////////////////////////////////////////////////////////////////////
 * main
 */

extern "C++"
int
libCLImate_program_main_Cpp(
  clasp::arguments_t const* args
)
{
  if(clasp::flag_specified(args, "--help"))
  {
    show_usage(args);
    return EXIT_SUCCESS;
  }

  if(clasp::flag_specified(args, "--version"))
  {
    show_version(args);
    return EXIT_SUCCESS;
  }

  clasp::verify_all_flags_and_options_are_recognised(args, libCLImate_aliases);

  if(0 == args->numValues)
  {
    ff::fmtln(std::cerr, "{0}: no pattern specified; use --help for usage\n", ToolName);

    return EXIT_FAILURE;
  }

  std::regex::flag_type   reflags = std::regex::flag_type(0);

  std::string const   pattern(args->values[0].value.ptr, args->values[0].value.len);
  std::regex const    re(pattern, reflags);
  std::string         line;

  for(; stlsoft::read_line(stdin, line); )
  {
    if(std::regex_match(line, re))
    {
      ff::writeln(std::cout, line);
    }
  }


  return EXIT_SUCCESS;
}

/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static void show_usage(clasp_arguments_t const* args)
{
  clasp_showUsage(
    args
  , libCLImate_aliases
  , ToolName, Summary, Copyright, Description, Usage
  , verMajor, verMinor, verRevision
  , clasp_showHeaderByFILE, clasp_showBodyByFILE, stdout
  , 0
  , 0
  , 4
  , 1
  );
}

static void show_version(clasp_arguments_t const* args)
{
  clasp_showVersion(
    args
  , ToolName
  , verMajor, verMinor, verRevision
  , clasp_showVersionByFILE, stdout
  , 0
  );
}

/* ///////////////////////////// end of file //////////////////////////// */
