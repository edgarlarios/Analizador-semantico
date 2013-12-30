#ifndef  __definiciones_
#define __definiciones_
#include <cstdlib>

typedef enum{ _id, _eof, error} tipolex;

extern void abrir(char*);
extern void cerrar();
extern tipolex scanner();
extern void lineaDeError();
extern void palabras();
extern int yyparse();
extern node*raiz;
extern float evaluate(node*);


extern void show(node*);





# endif
