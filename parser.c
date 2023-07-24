#include <stdio.h>
#include <stdlib.h>
#include <mpc_parser.h>


int main(){
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Wisp = mpc_new("Wisp");

  mpca_lang(MPCA_LANG_DEFAULT,
	   " \
	   number:/-?[0-9]+/; \
	   operator:'+'|'-'|'*'|'/'; \
	   expr:<number>|'('<operator><expr>+')';\
	   Wisp:/^<operator><expr>+/$/; \
	   ",
	   Number, Operator, Expr, Wisp);

  mpc_cleanup(4, Number, Operator, Expr,Wisp);
}
