
#ifndef TOKEN_H
#define TOKEN_H

#include "utils.h"

typedef enum {
  BIND_TOKEN,

  ADD_TOKEN,
  SUB_TOKEN,
  CMPL_TOKEN,
  NOT_TOKEN,

  MUL_TOKEN,
  FDIV_TOKEN,
  IDIV_TOKEN,
  MOD_TOKEN,
  POW_TOKEN,
  BIT_AND_TOKEN,
  BIT_OR_TOKEN,
  BIT_XOR_TOKEN,
  AND_TOKEN,
  OR_TOKEN,
  EQ_TOKEN,
  NEQ_TOKEN,
  GT_TOKEN,
  GTE_TOKEN,
  LT_TOKEN,
  LTE_TOKEN,
  SHR_TOKEN,
  USHR_TOKEN,
  SHL_TOKEN,

  COMMA_TOKEN,
  DOT_TOKEN,
  COLON_TOKEN,
  SEMICOLON_TOKEN,
  LPAREN_TOKEN,
  LBRACK_TOKEN,
  RPAREN_TOKEN,
  RBRACK_TOKEN,
  LBRACE_TOKEN,
  RBRACE_TOKEN,
  QUEST_TOKEN,

  IDENTIFIER_TOKEN,
  STRING_TOKEN,
  INTEGER_TOKEN,
  FLOAT_TOKEN,
  TRUE_TOKEN,
  FALSE_TOKEN,

  ERROR_TOKEN,
  EOF_TOKEN,
} token_type;

typedef struct {
  unsigned row;
  unsigned col;
} location;

typedef struct {
  location loc;
  char *line;
  char *value;
  unsigned length;
  token_type type;
} token_t;

typedef struct scanner_t scanner_t;

token_t make_token(scanner_t *s, token_type type);

void free_token(token_t *t);

#endif