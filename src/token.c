
#include "token.h"
#include "scanner.h"
#include "utils.h"

token_t make_token(scanner_t *s, token_type type) {
  unsigned length = s->current - s->start;
  char *value = allocate_chars(s->start, length);
  return (token_t){
      .type = type,
      .value = value,
      .length = length,
      .loc =
          (location){
              .row = s->loc.row,
              .col = s->loc.col - (length - 1),
          },
      .line = s->current_line,
  };
}

void free_token(token_t *token) { free(token->value); }