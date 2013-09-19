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
    char *separators;   //string of separators
    char *tokens;       //string of tokens
    int *firstIndex;
    int *secondIndex;
    short *arr;         //bitarray of separator chars
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
  short *arr;
  int i;
  char a;

  tokenizer = malloc(sizeof(TokenizerT));
  sep = (char *) malloc(strlen(separators)*sizeof(char)+1);
  tok = (char *) malloc(strlen(ts)*sizeof(char)+1);
  first = malloc(sizeof(int));
  second = malloc(sizeof(int));
  arr = calloc(256, sizeof(short));

  sep = strcpy(sep, separators);
  tok = strcpy(tok, ts);
  *first = 0;
  *second = 0;

  for (i = 0; i < 256; i++) {   //set bitarray to all zeros
    arr[i] = 0;
  }
  
  for(i=0; i<strlen(sep); i++) {    //create bitarray of separator chars

      if (sep[i] == '\\' && i < strlen(sep) - 1) {

         char c = sep[i + 1];

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
        a = sep[i];
        if (a != '\\') {    //true if i == strlen(sep)
            arr[a] = 1;
        }
      }

  }

  tokenizer->separators = sep;
  tokenizer->tokens = tok;
  tokenizer->firstIndex = first;
  tokenizer->secondIndex = second;
  tokenizer->arr = arr;

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
  free(tk->arr);
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

  short *arr = tk->arr;
  int *first = tk->firstIndex;
  int *second = tk->secondIndex;
  char *tkns = tk->tokens;
  char *seps = tk->separators;
  int i;
  char a;
  int escapes = 0;

  if (*second == strlen(tkns)) {    //true if entire token string has been parsed
      return NULL;
  }


  while (*second < strlen(tkns)) {  //this loop moves *second to the next non-separator character in tkns

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

  *first = *second; //move *first past the separators as well

  while (*second < strlen(tkns)) {  //this loop moves *second to the next separator

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
        escapes++;
        
    } else {
        a = tkns[*second];
        if (a == '\\') {    //*second == strlen(tkns) - 1
            escapes++;
        }
    } 

    if (arr[a] != 1) {
      (*second) += escape;
    } else {
      break;
    }

  }

  char *tempToken = calloc(*second - *first + 1 - escapes, sizeof(char));

  i=0;
  while(*first<*second){    //this loop puts the characters of the token in tempToken

     int escape = 1;

     if (tkns[*first] == '\\' && *first < strlen(tkns) - 1) {
       
        char c = tkns[*first + 1];

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
      a = tkns[*first];
      if (a == '\\') {  //*first == strlen(tkns) - 1
        (*first)++;
        break;
      }
    }

      tempToken[i] = a;
      (*first) += escape;
      i++;
  }

  tempToken[i] = '\0';

  return tempToken;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

  if(argc != 3) {
     printf("Error: arguments should be in the format: ./tokenizer 'separators' 'tokens'\n");
     return -1;
  }

  char *separators = argv[1];
  char *tokens = argv[2];
  TokenizerT *tokenizer = TKCreate(separators, tokens);
  
  char *currtoken = TKGetNextToken(tokenizer);
  while (currtoken != NULL) {

      int i;
      char c;
      //printf("%s\n", currtoken);
      for (i = 0; i < strlen(currtoken); i++) {
          c = currtoken[i];
          if (c == '\n') {
             printf("[0x%.2x]", c);
          } else if (c == '\v') {
             printf("[0x%.2x]", c);
          } else if (c == '\t') {
             printf("[0x%.2x]", c);
          } else if (c == '\b') {
             printf("[0x%.2x]", c);
          } else if (c == '\r') {
             printf("[0x%.2x]", c);
          } else if (c == '\f') {
             printf("[0x%.2x]", c);
          } else if (c == '\a') {
             printf("[0x%.2x]", c);
          } else if (c == '\"') {
             printf("[0x%.2x]", c);
          } else if (c == '\\') {
             printf("[0x%.2x]", c);
          } else {
             printf("%c", c);
          }
      }
      printf("\n");
	  free(currtoken);
      currtoken = TKGetNextToken(tokenizer);
  }

  TKDestroy(tokenizer);

  return 0;
}
