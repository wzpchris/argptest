#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

const char *argp_program_version = "argp-ex2 1.0";
const char *argp_program_bug_address = "<bug-gnu-utils&gnu.org>";
static char doc[] = "Argp example #2 -- a pretty minimal program using argp";

static struct argp argp = {0, 0, 0, doc};

int main(int argc, char **argv)
{
	argp_parse(&argp, argc, argv, 0, 0, 0);
	exit(0);
}
