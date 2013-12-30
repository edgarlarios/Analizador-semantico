#include "node.h"
#include "scanner.h"
#include "parser.hpp"
# define UDEF -1
# define tks 200
#include <fstream>
#include <string>
#include <cctype>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
FILE *p,*q;
string palabra;
int contador=1,i=0;
char EOL= '\n';
string tokens[tks];


char siguiente(){ return fgetc(p);}
void retroceso(){ fseek(p,-1,SEEK_CUR);}
void acepta(){ fseek(q, ftell(p), SEEK_SET);}
void falla(){ fseek(p, ftell(q), SEEK_SET);}


void abrir(char* fname){     
     p= fopen(fname, "r");
     q= fopen(fname, "r");
}


          
void cerrar(){ 
     fclose(p); 
     fclose(q);
}

void palabras(){
     tokens[i]=palabra;
     cout<<tokens[i];
     i++;
}

void lineaDeError(){
     cout<<contador;
}

bool wsp(){
     char c = siguiente(); 
     if(c== EOL){ 
         contador=contador+1;  
     }
     if(isspace(c)){
         acepta();
         return true;      
     }        
     else{ 
      falla();
      return false;
     }
}

bool eof(){
     char c= siguiente();
     if(c == EOF) return true;
     else return false;
}
              
     
int numerico(){
    
     palabra="";
     
     int actual=0, anterior, cont=0;;
     char c;
    char x[10];
     while(actual != UDEF){          
          anterior = actual;
          c = siguiente();  
          palabra+=c;
          
          if(c != isspace(c)){
          x[cont]=c;
          cont++;
          }
          switch(actual ){ 
                        
              case 0:                                   
                  if( c == '0' ) actual=1;
                  else if(isdigit(c) && c != '0') actual=6;
                  else actual= UDEF; 
                  break;
              case 1:                                    
                   if(isdigit(c) && c <= '7') actual=2;                    
                   else if (c == 'x' || c == 'X') actual = 3;
                   else actual= UDEF;
                   break;
              case 2:                   
                   if(isdigit(c) && c <= '7') actual=2; 
                   else actual= UDEF;
                   break;
              case 3:  
                   if(isdigit(c)) actual=4;
                   else if( c >= 'a' && c <= 'f') actual= 4;
                   else if( c >= 'A' && c <= 'F') actual= 4;                                                       
                                   
                   else actual= UDEF;
                   break;
               case 4:                                                 
                   if(isdigit(c)) actual=5;
                   else if( c >= 'a' && c <= 'f') actual= 5;
                   else if( c >= 'A' && c <= 'F') actual= 5;   
                   else actual= UDEF;
                   break;
                case 5:                       
                   if(isdigit(c)) actual=4;
                   else if( c >= 'a' && c <= 'f') actual= 4;
                   else if( c >= 'A' && c <= 'F') actual= 4;                                  
                   else actual= UDEF;
                   break;
                case 6:                                     
                   if(isdigit(c)) actual=6; 
                   else if(ispunct(c)) actual=7;
                   else actual= UDEF;
                   break;
                case 7:                    
                    if(isdigit(c)) actual=7;
                    else if(isalpha(c) && c== 'E') actual=8;
                    else if(isalpha(c) && c== 'e') actual=8;
                    else actual= UDEF;
                    break; 
                case 8:
                     if(isdigit(c)) actual=7;
                     else if(c == '+') actual=7;
                     else if(c == '-') actual=7;
                     else actual= UDEF;
                     break;  
                     
          }       
     }          
     
     if(anterior == 1 ||anterior == 2 || anterior==5 || anterior==6 || anterior==7  ){   
                                     
           acepta();    
           yylval.val = atof(x);        
           return NUM;
     }
        
falla();     
return error; 
}          

int delimitacion(){
     int actual=0, anterior;
     char c;
     palabra="";
     while(actual != UDEF){         
          anterior = actual;
          c = siguiente(); 
          palabra+=c;         
          switch(actual){ 
                        
                case 0:
                     if(c == '(') actual= 1;
                     else if( c == ')') actual= 2;
                     else if (c == '[') actual=3;
                     else if (c == ']') actual=4;
                     else actual = UDEF;
                     break;
                case 1:
                     actual = UDEF;
                     break;
                case 2:
                     actual = UDEF;
                     break;
                case 3:
                     actual = UDEF;
                     break;
                case 4:
                     actual = UDEF;
                     break;
                }
          }  
          if(anterior== 1){
                 acepta();
                 return '(';
          }
          if(anterior== 2){
                 acepta();
                 return ')';
          }
          if(anterior== 3){
                 acepta();
                 return '[';
          }
          if(anterior== 4){
                 acepta();
                 return ']';
          }
falla();
return error;

}

int AsigRelacionales(){
      int actual=0, anterior;
      char c;
      
      palabra="";   
    while(actual != UDEF){
       anterior = actual;
       c = siguiente();
       palabra+=c;  
       switch(actual){
           
         case 0:  
                           
                if(c == '<') actual = 1;
                else if(c == '=') actual = 3;
                else if( c == '>') actual = 5;
                else if( c == '!') actual = 7;
                else if(c == '?') actual=9;
                else  actual=UDEF;
                break;
           case 1:               
                if(c == '=') actual=2;
                else  actual=UDEF;
                break;
           case 2:                
                actual=UDEF;
                break;
           case 3:               
                if(c == '=') actual=4;
                else  actual=UDEF;
                break;
           case 4:             
                actual=UDEF;
                break;
          case 5:
               if(c == '=') actual=6;
               else  actual=UDEF;
               break;
          case 6:
                actual=UDEF;
                break;
          case 7:
               if(c == '=') actual=8;
               else  actual=UDEF;
               break;
          case 8:
                actual=UDEF;
                break;
          
          case 9:
                actual=UDEF;
                break;
         
          case 10:
                actual=UDEF;
                break;
          }
    } 
    if(anterior==1){
          
          acepta();
          return '<';
    } 
    if(anterior == 2){         
          acepta();
          return menIg;
    }   
    if(anterior == 3){         
          acepta();
          return '=';
    } 
    if(anterior == 4){      
          acepta();
          return igualdad;          
    } 
    if(anterior == 5){         
          acepta();
          return '>';
    } 
    if(anterior == 6){         
          acepta();
          return mayIg;
    } 
    if(anterior == 8){         
          acepta();
          return desig;
    } 
    if(anterior == 9){         
          acepta();
          return '?';
    } 
falla();     
return error; 

}   

int logicos(){
     int actual=0, anterior;
     char c;
     palabra="";
     while(actual != UDEF){         
          anterior = actual;
          c = siguiente(); 
          palabra+=c;         
          switch(actual){ 
                        
                case 0:                     
                     if(c == '!') actual=5;
                     else if(c == '|') actual=3;
                     else if(c == '&') actual=1;                     
                     else actual=UDEF;
                     break;
                 case 1:                      
                      if(c == '&') actual=2;
                      else actual=UDEF;
                      break;
                 case 2:                                     
                      actual=UDEF;
                      break;
                 case 3:                      
                      if(c == '|') actual=4;
                      else actual= UDEF;
                      break;
                 case 4:                                         
                      actual= UDEF;
                      break;
                 case 5:                     
                      actual= UDEF;
                      break;
          }
     }            
     if(anterior==2){
           acepta();
           return '&';
     }
     if(anterior == 4){
            acepta();
            return '|';
     }      
     if(anterior == 5){
             acepta();
             return '!';
     }
falla();     
return error; 
}

int aritmeticos(){
     int actual=0, anterior;
     char c;
     palabra="";
     
     while(actual != UDEF){        
          anterior = actual;
          c = siguiente();
          palabra+=c;
          switch(actual){ 
                        
                case 0:                                       
                     if(c == '+') actual= 1;
                     else if( c== '-') actual=2;
                     else if( c== '*') actual=3;
                     else if( c=='/') actual=4;
                     else actual= UDEF;
                     break;
                case 1:                                                                        
                      actual= UDEF;
                      break; 
                case 2:                                                       
                      actual= UDEF;
                      break;
                case 3:                                                       
                      actual= UDEF;
                      break; 
                case 4:                                                       
                      actual= UDEF;
                      break;                                      
          } 
     }    
     if(anterior== 1){
           acepta();
           return '+';
     }
     if(anterior== 2){
           acepta();
           return '-';
     }
     if(anterior== 3){
           acepta();
           return '*';
     }
     if(anterior== 4){
           acepta();
           return '/';
     }
falla();
return error;
}  
  
int Puntuacion(){
     int actual=0, anterior;
     char c; 
     palabra="";  
     while(actual != UDEF){          
          anterior = actual;
          c = siguiente();   
          palabra+=c;      
          switch(actual){                        
                case 0:                                            
                     if( c == '.') actual = 1;  
                     else if(c == ':') actual= 2;   
                     else if (c == ';') actual=3;
                     else actual = UDEF;
                     break;
                 case 1:                     
                     actual=UDEF;
                     break; 
                 case 2:                  
                     actual=UDEF;
                     break;
                 case 3:                   
                     actual=UDEF;
                     break;                       
          }
     } 
     if(anterior==1){
             acepta();
             return '.';
     }
     if(anterior==3){
             acepta();
             return ';';
     }
    if(anterior==2){
             acepta();
             return ':';
     }
  
falla();
return error;
}    

int identificador(){
     palabra="";
     int actual=0, anterior;
     char c;
     
     while(actual != UDEF){
          anterior = actual;
          c = siguiente();
          palabra+=c;
          switch(actual){
           
           case 0:
                if(isalpha(c)) actual = 2;
                else if (c== '_') actual=1;
                else actual = UDEF;
                break;
           
           case 1:
                if(isdigit(c) || c== '_') actual=1;  
                else if(isalpha(c)) actual=2;
                else actual= UDEF;
                break;
                
           case 2:
                if(isalnum(c)|| c == '_') actual=2;
                else actual= UDEF;
                break;
                
           }
     }    
     
     if (anterior==2){  
        if(palabra=="not "){
                  acepta();
                  return nott;
        } 
        if(palabra=="or "){
                  acepta();
                  return orr;
        }     
        if(palabra=="and "){
                  acepta();
                  return andd;
        }                                                                          
     
     }
falla(); 
return error;
}  

bool comentarios(){
     int actual=0, anterior;
     char c;
     palabra="";
     while(actual != UDEF){        
          anterior = actual;
          c = siguiente();
          
          switch(actual){ 
                        
                case 0:                    
                     if( c == '{') actual = 1;
                     else actual= UDEF;
                     break;
                case 1:
                     if(c != '}' && c != EOF) actual=1;                     
                     else if(c == EOF) actual=2;                     
                     else if(c == '}') actual=2;                                     
                     else actual= UDEF;
                     break; 
                case 2:                    
                     actual=UDEF;
                     break;
          }          
     }              
     if(anterior== 2){          
             acepta();
             return true;
     }
falla();
return false; 
} 

bool errores(){
     int actual=0, anterior;
     char c;
     
     while(actual != UDEF){        
          anterior = actual;
          c = siguiente();
          cout<<"ENTRAA"<<endl;
          switch(actual){ 
               case 0:                    
                    if(isdigit(c) || c == '_') actual=1;
                    else if(isalpha(c)){cout<<"entra"<<endl;  actual=1; }
                   if( c >= '!' && c <= '}') actual= 1;
                    else actual=UDEF;
                    break;
               case 1:              
                    if(isdigit(c)) actual=1;
                    if(isalpha(c)) actual=1;
                    if( c >= '!' && c <= '}') actual= 1;
                    else actual=UDEF;
                    break;
          }
     }
     if(anterior==1){
            acepta();
            return true;
     }
}

tipolex scanner(){
      
      while (wsp());
        tipolex l;
        if(eof()) return _eof;
        if(errores()) return error;      
}



int yylex (){
      
      while (wsp());
          int t;
         
        if((t = AsigRelacionales()) != error)  return t; 
        if((t=delimitacion()) != error) return t;  
        if((t=numerico()) != error)   return t; 
        if((t = logicos()) != error) return t;      
        if((t=aritmeticos()) != error) return t;  
        if((t=Puntuacion()) != error) return t;  
        if((t=identificador()) != error) return t;
                   
        
}
