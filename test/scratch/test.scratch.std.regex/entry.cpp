
/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* Pantheios header files - 1 */
#include <pantheios/pan.hpp>

#include <libclimate/main.hpp>

#include <regex>

/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

extern "C"
clasp::alias_t const libCLImate_aliases[] =
{
  // standard flags

  CLASP_FLAG( NULL,   "--help", "displays this help and exits"),
  CLASP_FLAG( NULL,   "--version", "displays version information and exits"),


  // program logic
};

/* /////////////////////////////////////////////////////////////////////////
 * main
 */

extern "C++"
int
libCLImate_program_main_Cpp(
  clasp::arguments_t const* args
)
{


    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */
