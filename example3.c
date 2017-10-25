#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

const char *argp_program_version = "argp-ex3 1.0";
const char *argp_progrm_bug_address = "<bug-gnu-utils@gnu.org>";
static char doc[] = "Argp example #3 -- a program with options and arguments using argp";

static char args_doc[] = "ARG1 ARG2";

static struct argp_option options[] = 
{
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"quite", 'q', 0, 0, "Don't produce any output"},
	{"silent", 's', 0, OPTION_ALIAS},
	{"output", 'o', "FILE", 0, "Output to FILE instead of standard output"},
	{0}
};

/*Used by main to communicate with parse_opt*/
struct arguments {
	char *args[2];
	int silent, verbose;
	char *output_file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	
	switch(key)
	{
		case 'q':case 's':
			arguments->silent = 1;
			break;
		case 'v':
			arguments->verbose = 1;
			break;
		case 'o':
			arguments->output_file = arg;
			break;
		case ARGP_KEY_ARG:
			if(state->arg_num >= 2)
				argp_usage(state); /*Too many arguments. */
			arguments->args[state->arg_num] = arg;
			break;
		case ARGP_KEY_END:
			if(state->arg_num < 2)
				argp_usage(state); /*NOT enough argument*/
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char **argv)
{
	struct arguments arguments;
	arguments.silent = 0;
	arguments.verbose = 0;
	arguments.output_file = "-";
	
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	printf("ARG1=%s\nARGP2=%s\nOUTPUT_FILE=%s\n"
			"VERBOSE=%s\nSILENT=%s\n",
			arguments.args[0], arguments.args[1],
			arguments.output_file,
			arguments.verbose ? "yes" : "no",
			arguments.silent ? "yes" : "no");
	exit(0);
}
