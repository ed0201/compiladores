#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>

// Morales Sanchez Eder Isa�  
// boleta: 2015301296 
// NOTA: por falta de conocimiento general sobre el proyecto puede que aun no identifique algunas palabras reservadas pero solo es cuestion de agregarlas
// aun asi el programa identifica las PR , los simbolos , las comparaciones como un solo <= y >= != etc. falta optimizarlo pero es un buen avance, quisiera que diera un detallado de lista
// donde diera cuales son las palabras y demas que identifico, en vez de solo mandar la cantidad de elementos pero es un avance simple sin bibliotecas con funciones regex.  
bool caso_simbolo(char c) {
    const char simbolos[] = "+-*/=<>";
    const int numero_sim = strlen(simbolos);   /*Funci�n booleana que verifica si el  car�cter es un s�mbolo  con forme va recorriendo el arreglo*/
    for (int i = 0; i < numero_sim; i++) {
        if (c == simbolos[i]) {
            return true;
        }
    }
    return false;
}


bool caso_digito(char c) {                   // Funci�n investigada que verifica si el car�cter  en turno es un n�mero*/
    return std::isdigit(c);        
}


bool caso_palabraR(const std::string& palabra) {                                     // Funci�n que verifica si una palabra es una palabra reservada recorriendola al completo para hacerlo y comparandola, dio muhca lata
    const char* PR[] = {"int", "float", "double", "char", "void" };
    const int numero_PR = sizeof(PR) / sizeof(PR[0]);
    for (int i = 0; i < numero_PR; i++) {
        if (palabra == PR[i]) {
            return true;
        }
    }
    return false;
}

int main() {  /* funcion main pedimos el texto en consola pero puedo hacer que lea un archivo .txt y de ahi saque la info */
 
    std::cout << "Ingrese un texto:" << std::endl;                 
    std::string text;
    std::getline(std::cin, text);

    
    int numero_PR = 0;
    int numero_sim = 0;             /* contadores*/
    int numero_digitos = 0;
    std::vector<std::string> PR;
    std::vector<std::string> simbolos;           /*strings para cada caso*/
    std::vector<std::string> digitos;
    std::string palabra_actual;
    for (std::string::size_type i = 0; i < text.length(); i++) {
        char c = text[i];
        if (std::isspace(c)) {
            if (!palabra_actual.empty()) {
                if (caso_palabraR(palabra_actual)) {
                    numero_PR++;
                    PR.push_back(palabra_actual);
                } else if (caso_digito(palabra_actual[0])) {
                    numero_digitos++;
                    digitos.push_back(palabra_actual);
                }
                palabra_actual.clear();
            }
        } else if (caso_simbolo(c)) {
            if (!palabra_actual.empty()) {
                if (caso_palabraR(palabra_actual)) {
                    numero_PR++;
                    PR.push_back(palabra_actual);
                } else if (caso_digito(palabra_actual[0])) {
                    numero_digitos++;
                    digitos.push_back(palabra_actual);
                }
                palabra_actual.clear();
            }
            numero_sim++;
            std::string simbolo;
            simbolo.push_back(c);
            if (c == '=' && i + 1 < text.length() && text[i+1] == '=') {
                simbolo.push_back(text[i+1]);
                i++;
            } else if (c == '<' && i + 1 < text.length() && text[i+1] == '=') {
                simbolo.push_back(text[i+1]);
                i++;
            } else if (c == '>' && i + 1 < text.length() && text[i+1] == '=') {
                simbolo.push_back(text[i+1]);
                i++;
            } else if (c == '!' && i + 1 < text.length() && text[i+1] == '=') {
                simbolo.push_back(text[i+1]);
                i++;
            }
            simbolos.push_back(simbolo);
        } else {
            palabra_actual.push_back(c);
        }
    }

    
    if (!palabra_actual.empty()) {
        if (caso_palabraR(palabra_actual)) {
            numero_PR++;												/* solo en caso que la ultima palabra si no tiene un espacio para contemplar el caso posible */
        } else if (caso_digito(palabra_actual[0])) {
            numero_digitos++;
        }
    }

  
    std::cout << "N�mero de palabras reservadas encontradas: " << numero_PR << std::endl;
    std::cout << "N�mero de simbolos encontrados: " << numero_sim << std::endl;                  /* imprimimos los contadores respectivos de cada caso analizado*/
    std::cout << "N�mero de numeros encontrados: " << numero_digitos << std::endl;

    return 0;
}
