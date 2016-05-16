#ifndef TABULEIRO_H_
#define TABULEIRO_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define HEURISTICA_1_ 0
#define HEURISTICA_2_ 1
#define HEURISTICA_3_ 2
#define HEURISTICA_4_ 3
#define HEURISTICA_5_ 4
#define PESO_H1_ 0.08
#define PESO_H2_ 0.02
#define PESO_H3_ 0.90

class Tabuleiro
{
	private:
		string id;
		int g;
		int f;
		int heuristica;
		string p;

	public:
		int casa[16];
		Tabuleiro();
		~Tabuleiro();
		const bool operator<(const Tabuleiro rhs) const;
		string Calcula_ID();
		int Calcula_H();
		int Le_Tabuleiro_STDIN();
		void Imprime_Tabuleiro();
		void SetHeuristica(int heuristica) {this->heuristica = heuristica;}
		int Get_G() const {return this->g;}
		int Get_F() const {return this->f;}
		int Get_H() const {return ((this->f) - (this->g));}
		string Get_ID() const {return this->id;}
		string Get_P() const {return this->p;}
		void Set_ID(string id) {this->id = id;}
		void Set_G(int g) {this->g = g;}
		void Set_P(string p) {this->p = p;}
		void Gerar_Vizinhos(vector <Tabuleiro> &lista);
};

#endif
