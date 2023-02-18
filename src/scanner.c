
#include "scanner.h"
#include "token.h"
#include "utils.h"

char *get_next_line(const char *__src) {
  unsigned length = 0;
  for (const char *c = __src; *c != '\n' && *c != '\0'; c++, length++) {
    ;
  }
  return allocate_chars(__src, length);
}

static bool is_quest(char c) { return c == '?'; }

static bool is_at_end(const scanner_t *s) { return *s->current == '\0'; }

static bool is_digit(char c) { return c >= '0' && c <= '9'; }

static bool is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool is_und(char c) { return c == '_'; }

static char peek_current(const scanner_t *s) { return *s->current; }

static char peek_next(const scanner_t *s) {
  return is_at_end(s) ? '\0' : s->current[1];
}

static char advance(scanner_t *s) {
  s->current++;
  s->loc.col++;
  return s->current[-1];
}

static bool match(scanner_t *s, char expected) {
  return !is_at_end(s) && *s->current == expected && advance(s);
}

static void new_line(scanner_t *s) {
  advance(s);
  free(s->current_line);
  s->current_line = get_next_line(s->current);
  s->loc.row++;
  s->loc.col = 0;
}

static void skip_line_comment(scanner_t *s) {
  while (peek_current(s) != '\n' && !is_at_end(s)) {
    advance(s);
  }
}

static void skip_block_comment(scanner_t *s) {
  advance(s);
  advance(s);
  unsigned blocks = 1;
  do {
    if (is_at_end(s)) {
      return;
    }

    if (peek_current(s) == '/' && peek_next(s) == '*') {
      advance(s);
      advance(s);
      blocks++;
      continue;
    }

    if (peek_current(s) == '*' && peek_next(s) == '/') {
      advance(s);
      advance(s);
      if (blocks != 0) {
        blocks--;
      }
      continue;
    }

    advance(s);
  } while (blocks > 0);
}

static void skip_whitespace(scanner_t *s) {
  while (true) {
    switch (peek_current(s)) {
    case ' ':
    case '\r':
    case '\t':
      advance(s);
      break;
    case '\n':
      new_line(s);
      break;
    case '/': {
      if (peek_next(s) == '/') {
        skip_line_comment(s);
        break;
      } else if (peek_next(s) == '*') {
        skip_block_comment(s);
        break;
      }
      return;
    }
    default:
      return;
    }
  }
}

token_t scan_token(scanner_t *s) {
  skip_whitespace(s);
  s->start = s->current;
  if (is_at_end(s)) {
    return make_token(s, EOF_TOKEN);
  }
}

scanner_result scan_file(const char *const file_path) {
  if (access(file_path, F_OK) != 0) {
    printf(FILE_DOES_NOT_EXISTS, file_path);
    return SCANNER_FILE_ERROR;
  }

  if (access(file_path, R_OK) != 0) {
    printf(FILE_CANT_BE_READ, file_path);
    return SCANNER_FILE_ERROR;
  }

  FILE *file = fopen(file_path, "rb");

  fseek(file, 0L, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  char *source = malloc(file_size + 1);
  unsigned long bytes_read = fread(source, sizeof(char), file_size, file);
  source[bytes_read] = '\0';
  fclose(file);

  scanner_t scanner = {
      .start = source,
      .current = source,
      .current_line = get_next_line(source),
      .loc = {.col = 0, .row = 1},
  };

  free(scanner.current_line);
  free(source);

  return SCANNER_OK;
}