
/*typedef enum{_error, _opAsig,_mayQ,_menQ,_mayIg,_menIg, _desig ,_igualdad,
             _opConj, _opDisy, _opNeg, _rest, _sum, _mult, _div, 
              _punto, _dosPuntos, _interrogativo, _num, _or, _not} yylex;*/
                         
#ifndef __nodes_
#define __nodes_

typedef enum {_sum, _mult, _desig, _rest, _div, _num, _rel, 
_menQ, _mayQ, _menIg, _mayIg, _igualdad, _interrogativo,_dosPuntos, _dif,
 _opConj, _opDisy, _opNeg, _not, _parIzq, _parDer, _selectlogico } tnode;

typedef struct snode{
	tnode type;
	float value;
	struct snode *left;
	struct snode *middle;
	struct snode *right;
} node;


#endif
