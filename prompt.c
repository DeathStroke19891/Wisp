#include <stdio.h>
#include <stdlib.h>
#include <mpc_parser.h>

#ifdef _WIN32

#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy(strlen(cpy) -1] = '\0';
  return cpy;
}

void add_history(char *unused) {}

#else

#include <readline/history.h>
#include <readline/readline.h>

#endif

static char input[2048];

int main(int argc, char **argv) {
  
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Wisp = mpc_new("wisp");

  mpca_lang(MPCA_LANG_PREDICTIVE,
            " number   : /-?[0-9]+/;                                  "
	    " operator : '+' | '-' | '*' | '/';                       "
	    " expr     : <number> | '(' <operator> <expr>+ ')';       "
	    " wisp     : /^/ <operator> <expr>+ /$/;                  ",
            Number, Operator, Expr, Wisp, NULL);

  puts("Wisp Version 0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1) {   
    char *input = readline("Wisp> ");
    add_history(input);
    printf("%s\n", input);
    
    mpc_result_t r;
    if (mpc_parse("<stdin>",input,Wisp,&r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
  }
  mpc_cleanup(4, Number, Operator, Expr, Wisp);
  free(input);
  return 0;
}
