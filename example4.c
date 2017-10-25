#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <argp.h>

const char *argp_program_version = "argp-ex4 1.0";
const char *argp_program_bug_address = "<bug-gnu-util@prep.ai.mit.edu>";
static char doc[] = "Argp example #4 -- a program with somewhat more complicated\
	\noptions\
	\vThis part of the documentation comes *after* the options;\
	\nnote that the text is automatically filled, but it's possible\
	to force a line-break, e.g. \n<-- here.";
static char args_doc[] = "ARG1 [STRING...]";
#define OPT_ABORT 1
static struct argp_option options[] = {
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"quiet", 'q', 0, 0, "Don't produce any output"},
	{"silent", 's', 0, OPTION_ALIAS},
	{"output", 'o', "FILE", 0, "Output to FILE instead of standard output"},
	{0, 0, 0, 0, "The following options should be grouped together:"},
	{"repeat", 'r', "COUNT", OPTION_ARG_OPTIONAL, "Repeat the output COUNT(default 10) times"},
	{"abort", OPT_ABORT, 0, 0, "Abort before showing any output"},
	{0}
};

struct arguments 
{
	char *arg1;
	char **strings;
	int silent, verbose, abort;
	char *output_file;
	int repeat_count;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch(key)
	{
		case 'q': case 's':
			arguments->silent = 1;
			break;
		case 'v':
			arguments->verbose = 1;
			break;
		case 'o':
			arguments->output_file = arg;
			break;
		case 'r':
			arguments->repeat_count = arg ? atoi(arg) : 10;
			break;
		case OPT_ABORT:
			arguments->abort = 1;
			break;
		case ARGP_KEY_NO_ARGS:
			argp_usage(state);
		case ARGP_KEY_ARG:
			/*Here we know that state->arg_num == 0, since we force argument parsing to end before any more arguments can get here.*/
			arguments->arg1 = arg;
			arguments->strings = &state->argv[state->next];
			state->next = state->argc;
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};
int main(int argc, char **argv)
{
	int i, j;
	struct arguments arguments;
	arguments.silent = 0;
	arguments.verbose = 0;
	arguments.output_file = "-";
	arguments.repeat_count = 1;
	arguments.abort = 0;
	
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	if(arguments.abort)
		error(10, 0, "ABORTED");

	for(i = 0; i < arguments.repeat_count; ++i)
	{
		printf("ARG1=%s\n", arguments.arg1);
		printf("STRINGS = ");
		for(j = 0; arguments.strings[j]; ++j)
			printf(j == 0 ? "%s" : ", %s", arguments.strings[j]);
		printf("\n");
		printf("OUTPUT_FILE = %s\nVERBOSE = %s\nSILENT = %s\n",
				arguments.output_file, 
				arguments.verbose ? "yes" : "no",
				arguments.silent ? "yes" : "no");
	}

	exit(0);
}
