
#include "node.h"
#include<cstdio>
#include <iostream>
#include "parser.hpp"
#include "scanner.h"
#include<cstdlib>

using namespace std;
int n=0;
int main(){
    
    abrir("prueba.txt");
   
    yyparse();
    
    
    show(raiz);
    
    cout<<endl;
    if(evaluate(raiz)== 1 && n==2) cout<<"verdadero"<<endl;
    else if(evaluate(raiz)==0 && n==2) cout<<"falso"<<endl;
    else{
         cout<<"resultado: "<<evaluate(raiz)<<endl;
    }             
    
     tipolex l;
     l= scanner(); 
     if(l == _eof){ cout<<"fin de archivo"<<endl; }
     if(l == error){
           cout<<"error"<<endl;
           cerrar();
     
     }
    


cerrar();
  
  system("PAUSE");
  return EXIT_SUCCESS;
}

void show(node *p){
	switch( p -> type){
            
            
		case _sum:
             if(n==0) n=1;
            cout<<"|| suma"<<endl;cout<<"|";
			show(p->left);cout<<"|";
			show(p->right);
			break;
			
		case _mayQ:
            if(n==0) n=2; 
            cout<<"| mayor que"<<endl;
			show(p ->left);
			show(p->right);
			break;
			
		case _menQ:
            if(n==0) n=2; 
            cout<<"| menor que"<<endl;
			show(p ->left);
			show(p->right);
			break;
			
		case _menIg:
              if(n==0) n=2; 
             cout<<"| menor igual"<<endl;
			show(p ->left);
			show(p->right);
			cout<<"|";
			break;
			
		case _mayIg:
              if(n==0) n=2; 
             cout<<"| mayor igual"<<endl;
			show(p ->left);
			show(p->right);
			cout<<"|";
			break;
			
		case _igualdad:
            if(n==0) n=2; 
            cout<<"| igualdad"<<endl;
			show(p ->left);
			show(p->right);
			cout<<"|";
			break;
			
		case _desig:
              if(n==0) n=2; 
             cout<<"| diferente de"<<endl;
			show(p ->left);
			show(p->right);
			cout<<"|";
			break;

		case _mult:
             if(n==0) n=1;
             cout<<"|| multiplicacion"<<endl;cout<<"|";
			show(p ->left);cout<<"|";
			show(p->right);
			break;
			
		case _rest:
            if(n==0) n=1;
			if(p->right) {
                cout<<"|| resta"<<endl;cout<<"|";
				show(p ->left);cout<<"|";
				show(p->right);
				
			} else{
				show(p->left);				
			}
			break;
			
		case _div:
             if(n==0) n=1;
             cout<<"|| division"<<endl;cout<<"|";
			show(p ->left);cout<<"|";
			show(p->right);
			break;
			
		case _opConj:
            if(n==0) n=2; 
            cout<<"conjuncion"<<endl;
            show(p ->left);
		    show(p->right);
			break;
		
		case _opDisy:
            if(n==0) n=2; 
            cout<<"disyuncion"<<endl;
            show(p ->left);
		    show(p->right); 
			break;
		
		case _not:
            if(n==0) n=2; 
            cout<<"negacion"<<endl;
            show(p ->left);
			break;
			
		case _selectlogico:
            cout<<"selector logico"<<endl;
            show(p ->left);
            show(p->middle);
		    show(p->right);
			break;
			
		case _num:
			cout<<"|| Numero: "<<p->value<<endl;
     }
}   
     
     
float evaluate(node *p){
       float r;
	switch( p -> type){
            
       	case _selectlogico:
              if(evaluate(p->left)==0) return evaluate(p->right);
              else return evaluate(p->middle);              
              break;
              
		case _sum: 
              r = evaluate(p->left) + evaluate(p->right);
              return r;
              break;
  
       case _rest: 
              r = evaluate(p->left) - evaluate(p->right);
              return r;
              break;
       
       case _mult: 
              r = evaluate(p->left) * evaluate(p->right);              
              return r;
              break;
              
       case _div: 
              r = evaluate(p->left) / evaluate(p->right);
              return r;
              break;                          
              
          case _num:
			r= p-> value;
  	return r;
		 break;
       
       case _mayQ:
           if( evaluate(p->left) > evaluate(p->right)) return 1;          
           else return 0; 
			break;
			
		case _menQ:
            
			if( evaluate(p->left) < evaluate(p->right)) return 1;
            else return 0;	
			break;
			
		case _menIg:
             if( evaluate(p->left) <= evaluate(p->right)) return 1;          
             else return 0; 
	         break;
			
			break;
			
		case _mayIg:
             if( evaluate(p->left) >= evaluate(p->right)) return 1;          
             else return 0; 
	         break;
			
		case _igualdad:
            if( evaluate(p->left) == evaluate(p->right)) return 1;          
             else return 0; 			
			break;
			
		case _desig:
            if( evaluate(p->left) != evaluate(p->right)) return 1;          
             else return 0; 			
			break;
			
		case _opDisy:
             if( evaluate(p->left) != 0 && evaluate(p->right)!=0 ) return 1;
             else if( evaluate(p->left) == 0 && evaluate(p->right)==0 ) return 0;	
             else if( evaluate(p->left) == 0 && evaluate(p->right)!=0 ) return 0;	
             else if( evaluate(p->left) != 0 && evaluate(p->right)==0 ) return 0;			
 	         break;  
  
     	case _opConj:
             if( evaluate(p->left) != 0 && evaluate(p->right) !=0 ) return 1;
             else if( evaluate(p->left) == 0 && evaluate(p->right)==0 ) return 0;	
             else if( evaluate(p->left) == 0 && evaluate(p->right) !=0 ) return 1;	
             else if( evaluate(p->left) != 0 && evaluate(p->right)==0 ) return 1;			
 	         break; 
              
     	case _not:
             if( evaluate(p->left) != 0  ) return 0;
             else if( evaluate(p->left) == 0  ) return 1;				
 	         break; 
             
}

}
   

