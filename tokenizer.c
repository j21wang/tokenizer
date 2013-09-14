/*
 * a
 * Kevin Sung, Joyce Wang
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    char *separators;
    char *tokens;
    int *firstIndex;
    int *secondIndex;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
  TokenizerT *tokenizer;
  char *sep;
  char *tok;
  int *first;
  int *second;

  tokenizer = malloc(sizeof(TokenizerT));
  sep = (char *) malloc(strlen(separators)*sizeof(char)+1);
  tok = (char *) malloc(strlen(ts)*sizeof(char)+1);
  first = malloc(sizeof(int));
  second = malloc(sizeof(int));

  sep = strcpy(sep, separators);
  tok = strcpy(tok, ts);
  *first = 0;
  *second = 0;

  tokenizer->separators = sep;
  tokenizer->tokens = tok;
  tokenizer->firstIndex = first;
  tokenizer->secondIndex = second;

  return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
  free(tk->separators);
  free(tk->tokens);
  free(tk->firstIndex);
  free(tk->secondIndex);
  free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

  short arr[256];
  int *first = tk->firstIndex;
  int *second = tk->secondIndex;
  char *tkns = tk->tokens;
  char *seps = tk->separators;

  if (*second == strlen(tkns)) {
      return NULL;
  }

  //arr = calloc(256,sizeof(short));

  int i;
  for(i=0; i<strlen(seps); i++) {

      if (seps[i] == '\\' && i < strlen(seps) - 1) {

	char a;
        char c = seps[i + 1];

	if (c == 'n') {
		a = '\n';
	} else if (c == 'v') {
		a = '\v';
	} else if (c == 't') {
		a = '\t';
	} else if (c == 'b') {
		a = '\b';
	} else if (c == 'r') {
		a = '\r';
	} else if (c == 'f') {
		a = '\f';
	} else if (c == 'a') {
		a = '\a';
	} else {
		a = c;
	}

	arr[a] = 1;
	i++;

      } else {
        arr[seps[i]] = 1;
      }

  }

  int a;

  while (1) {

    int escape = 1;

    if (tkns[*second] == '\\' && *second < strlen(tkns) - 1) {
       
        char c = tkns[*second + 1];

	if (c == 'n') {
		a = '\n';
	} else if (c == 'v') {
		a = '\v';
	} else if (c == 't') {
		a = '\t';
	} else if (c == 'b') {
		a = '\b';
	} else if (c == 'r') {
		a = '\r';
	} else if (c == 'f') {
		a = '\f';
	} else if (c == 'a') {
		a = '\a';
	} else {
		a = c;
	}

        escape = 2;
        
    } else {
      a = tkns[*second];
    } 

    if (arr[a] == 1) {
      (*second) += escape;
    } else {
      break;
    }

  }

  *first = *second;

  while(arr[tkns[*second]] != 1 && *second < strlen(tkns)) {
      (*second)++;
  }

  char tempToken[*second-*first+1]; //check!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  char *tokenPtr = tempToken;

  i=0;
  while(*first<*second){
      tempToken[i] = tkns[*first];
      (*first)++;
      i++;
  }
  tempToken[i] = '\0';

  return tokenPtr;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

  char *separators = argv[1];
  char *tokens = argv[2];
  TokenizerT *tokenizer = TKCreate(separators, tokens);
  //printf("%s\n%s\n", tokenizer->separators, tokenizer->tokens);
  
  char *currtoken = TKGetNextToken(tokenizer);
  while (currtoken != NULL) {
      printf("%s\n", currtoken);
      currtoken = TKGetNextToken(tokenizer);
  }

  TKDestroy(tokenizer);

  return 0;
}
