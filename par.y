


%{


#include <cstdio>
#include "node.h"
extern int yylex(void);
int yyerror(const char *);



float resultado;


node *creaNodo(tnode, float); //nodos terminales
node *creaNodo(tnode, node*); //NOdos unarios (negaciones)
node *creaNodo(tnode, node *, node *); //Nodos binarios
node *creaNodo(tnode, node *, node *, node *); //Nodos trinario

node *raiz;
%}


%union{

   node *enlace;
   float val;
}

%token <val> NUM
%token mayIg
%token menIg
%token igualdad
%token desig
%token nott
%token orr
%token andd
%token error



%type <enlace> quest
%type <enlace> prop
%type <enlace> clause
%type <enlace> conj
%type <enlace> rel
%type <enlace> exp
%type <enlace> term
%type <enlace> fact

%%

begin: quest {raiz = $1;};

quest:
    prop '?' quest ':' quest   { $$ = creaNodo(_selectlogico, $1, $3, $5);};
    | prop     { $$ = $1;};



prop :
     prop orr clause  { $$ = creaNodo(_opConj, $1, $3);};
     | clause        { $$ = $1;};


clause: 
       clause andd conj  { $$ = creaNodo(_opDisy, $1, $3);};
       | conj   { $$ = $1;};


conj: 
      rel { $$= $1 ;};
      | exp { $$ = $1;};



rel:
     exp '<' exp    { $$ = creaNodo(_menQ, $1, $3);};
     | exp '>' exp  { $$ = creaNodo(_mayQ, $1, $3);};
     | exp mayIg exp { $$ = creaNodo(_mayIg, $1, $3);};
     | exp menIg exp { $$ = creaNodo(_menIg, $1, $3);};
     | exp igualdad exp { $$ = creaNodo(_igualdad, $1, $3);};
     | exp desig exp { $$ = creaNodo(_desig, $1, $3);};




exp : 
     exp '+' term  { $$ = creaNodo(_sum, $1, $3);};
     | exp '-' term  { $$ = creaNodo(_rest, $1, $3);};
     | term  { $$ = $1;}
;



term :
       term '*' fact  { $$ = creaNodo( _mult, $1, $3);};
       | term '/' fact  { $$ = creaNodo(_div, $1, $3);};
       | fact  { $$ = $1;};



fact :
      '-' fact  {$$= creaNodo ( _rest, $2);};
      | nott fact {$$ = creaNodo ( _not,  $2);};
      |'(' quest ')'{ $$= $2;};
      | NUM   {$$ = creaNodo (_num, $1);};





%%

node *creaNodo(tnode t, float v){  // nodos terminales
   
   node *p = new node;
   p-> type = t;
   p-> value = v;
   p-> left = NULL;
   p-> right = NULL;
   
   return p;
}

  node *creaNodo (tnode t, node*l){ //nodos unitarios (negacion)

   node *p = new node;
   p-> type= t;
   p-> value = 0.0;
   p-> left = l;
   p-> right = NULL;
   
   return p;
}


  node *creaNodo (tnode t, node*l,node*r){

   node *p = new node;
   p-> type=t;
   p-> value =0.0;
   p->left= l;
   p-> right = r;
   p-> middle = NULL;
   return p;
}

node *creaNodo (tnode t, node*l,node*m, node*r){

   node *p = new node;
   p-> type=t;
   p-> value =0.0;
   p->left= l;
   p-> middle = m ;
   p-> right = r ;
  
   
   return p;
}

int yyerror (const char *mssg){
}


