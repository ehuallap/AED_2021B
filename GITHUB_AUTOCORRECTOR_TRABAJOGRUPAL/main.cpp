#include <iostream>
#include <fstream>
#include <queue> 
#include "ListaDoblemente.h"

using namespace std;
void showq(queue<string> gq)
{
    queue<string> g = gq;
    while (!g.empty()) {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}
unsigned int edit_distance(const std::string& s1, const std::string& s2)
{
	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector <std::vector <unsigned int> > d(len1 + 1, std::vector <unsigned int >(len2 + 1));
	
	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;
	for(unsigned int i = 1; i <= len1; ++i)
	for(unsigned int j = 1; j <= len2; ++j)
	// note that std::min({arg1 , arg2 , arg3}) works only in C++11 ,
	// for C++98 use std::min(std::min(arg1 , arg2), arg3)
	d[i][j] = std::min(std::min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
	return d[len1][len2];
}

void escribir_output(doubleList<string>& input, doubleList<string>& dict) {
    Nodo<string> * itr_busqueda = input.m_pHead;
    Nodo<string> * itr_dict = dict.m_pHead;
    while(itr_busqueda){
		itr_dict = dict.m_pHead;
		queue<pair<string, int> > coincidencias;
		unsigned int dist_inicio = edit_distance(itr_busqueda -> m_dato, itr_dict -> m_dato);
		coincidencias.push(make_pair(itr_dict->m_dato, dist_inicio));
		itr_dict = itr_dict -> m_pSig;
		while(itr_dict) {
			unsigned int dist = edit_distance(itr_busqueda -> m_dato, itr_dict -> m_dato);
			if(dist == coincidencias.front().second) coincidencias.push(make_pair(itr_dict->m_dato, dist));
			if(dist < coincidencias.front().second) {
				while(!coincidencias.empty()) coincidencias.pop();
				coincidencias.push(make_pair(itr_dict->m_dato, dist));
			}
			itr_dict = itr_dict -> m_pSig;  
		}
        queue<pair<string, int>> auxiliar = coincidencias;
        cout << "\n\tSELECCIONE UNA OPCION: " << endl;
        int contador = 1;
		while(!auxiliar.empty()) {
			cout << "OPCION "<< contador++ << " : " << auxiliar.front().first << ' ' << ", MARGEN DE " << auxiliar.front().second << endl;
			auxiliar.pop();
		}
        int opcion;
        if (coincidencias.size() != 1) {
            do{
                cout << "INGRESAR OPCION PARA REEMPLAZAR: ";
                cin >> opcion;
            }while(opcion <= 0 || opcion > coincidencias.size());
            int posicion = opcion;
            while(--posicion) coincidencias.pop();
            itr_busqueda -> m_dato = coincidencias.front().first;
        } else{
            itr_busqueda -> m_dato = coincidencias.front().first;
        }
		cout << '\n';
		itr_busqueda = itr_busqueda -> m_pSig;
    }
    ofstream output("C:/Users/Usuario/Desktop/UNSA/2021 B/ALGORITMOS Y ESTRUCTURAS DE DATOS/EJERCICIO 2/EJERCICIO_2/OUTPUT.txt");
    Nodo<string>* tmp = input.m_pHead;
    while(tmp) {
        output << tmp->m_dato << '\n';
        tmp = tmp->m_pSig;
    }
    input.print();
}

int main()
{
    /*******************************
     * Josue Gabriel Sumare Uscca
     * Levi Joel Castillon Urquiza 
     * Julio Enrique Yauri Ituccayasi
     * Erick Klendort Hualla Puelles
    ********************************/
    doubleList<string> Inputs;
    doubleList<string> Diccionario;

    string ubicacion_input = "C:/Users/Usuario/Desktop/UNSA/2021 B/ALGORITMOS Y ESTRUCTURAS DE DATOS/EJERCICIO 2/EJERCICIO_2/INPUT.txt";
    string ubicacion_diccionario = "C:/Users/Usuario/Desktop/UNSA/2021 B/ALGORITMOS Y ESTRUCTURAS DE DATOS/EJERCICIO 2/EJERCICIO_2/ENGLISH.txt";
    string palabra;
    //Intoduce en la variable palabra el diccionario
    ifstream diccionario(ubicacion_diccionario);
    while(!diccionario.eof()) {
        diccionario >> palabra;
        Diccionario.push_back(palabra);
    }
    diccionario.close();
    palabra = "";
    
    //Introduce en la variable palabra nuestras palabras a comparar
    ifstream input(ubicacion_input);
    while(!input.eof()) {
        input >> palabra;
        Inputs.push_back(palabra);
    }
    input.close();
    if (Inputs.m_pHead->m_dato != "")
        escribir_output(Inputs, Diccionario);
    return 0;
}
