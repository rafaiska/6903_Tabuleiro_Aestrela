#include "tabuleiro.h"

//Para heuristica 2: Ordem numerica no tabuleiro.
const int caracol[16] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9};

//Para heuristica 3: Posicao ideal de cada casa
const int pos_ideal[16] = {9, 0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10};

Tabuleiro::Tabuleiro()
{
	this-> g = 0;
}

Tabuleiro::~Tabuleiro()
{

}

const bool Tabuleiro::operator<(const Tabuleiro rhs) const
{
	if(this->f > rhs.Get_F())
	{
		return true;
	}
	else if(this->f == rhs.Get_F())
	{
		if(this->id.compare(rhs.Get_ID()) > 0)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Tabuleiro::Gerar_Vizinhos(vector <Tabuleiro> &lista)
{
	int espaco_branco;

	//Encontra o espaco em branco
	for(int i=0; i<16; ++i)
		if(this->casa[i] == 0)
		{
			espaco_branco = i;
			break;
		}

	//Caso 1: branco nao esta na borda esquerda
	//Nesse caso o branco pode trocar com a peca a esquerda
	if(espaco_branco % 4 != 0)
	{
		Tabuleiro novo;
		for(int i=0; i<16; ++i)
		{
			if(espaco_branco == i+1)
			{
				novo.casa[i] = 0;
				++i;
				novo.casa[i] = this->casa[i-1];
			}
			else
				novo.casa[i] = this->casa[i];
		}
		novo.Set_G(this->g +1);
		novo.Set_P(this->id);
		novo.Calcula_ID();
		novo.SetHeuristica(this->heuristica);
		novo.Calcula_H();
		lista.push_back(novo);	
	}
	//Caso 2: branco nao esta na borda direita
	//Nesse caso pode-se trocar branco pela casa a direita	
	if(espaco_branco % 4 != 3)
	{
		Tabuleiro novo;
		for(int i=0; i<16; ++i)
		{
			if(espaco_branco == i)
			{
				novo.casa[i] = this->casa[i+1];
				++i;
				novo.casa[i] = 0;
			}
			else
				novo.casa[i] = this->casa[i];
		}
		novo.Set_G(this->g +1);
		novo.Set_P(this->id);
		novo.Calcula_ID();
		novo.SetHeuristica(this->heuristica);
		novo.Calcula_H();
		lista.push_back(novo);	
	}

	//Caso 3: branco nao esta na borda superior
	//Nesse caso, pode-se trocar o branco pelo elemento de cima
	if(espaco_branco > 3)
	{
		Tabuleiro novo;
		for(int i=0; i<16; ++i)
		{
			if(espaco_branco == i+4)
			{
				novo.casa[i] = 0;
				novo.casa[i+4] = this->casa[i];
			}
			else if(espaco_branco == i)
				continue;
			else
				novo.casa[i] = this->casa[i];
		}
		novo.Set_G(this->g +1);
		novo.Set_P(this->id);
		novo.Calcula_ID();
		novo.SetHeuristica(this->heuristica);
		novo.Calcula_H();
		lista.push_back(novo);	
	}

	//Caso 4: Branco nao esta na borda inferior
	//Nesse caso, pode-se trocar o branco pelo elemento de baixo
	if(espaco_branco < 12)
	{
		Tabuleiro novo;
		for(int i=0; i<16; ++i)
		{
			if(espaco_branco == i)
			{
				novo.casa[i+4] = 0;
				novo.casa[i] = this->casa[i+4];
			}
			else if(espaco_branco == i-4)
				continue;
			else
				novo.casa[i] = this->casa[i];
		}
		novo.Set_G(this->g +1);
		novo.Set_P(this->id);
		novo.Calcula_ID();
		novo.SetHeuristica(this->heuristica);
		novo.Calcula_H();
		lista.push_back(novo);	
	}
}

int Tabuleiro::Calcula_H()
{
	int h1, h2, h3, h4, h5;

	//HEURISTICA 1: NUMERO DE PECAS DESLOCADAS DO TABULEIRO
	if(this->heuristica == HEURISTICA_1_ || this->heuristica == HEURISTICA_4_ || this->heuristica == HEURISTICA_5_)
	{
		h1 = 0;

		if(this->casa[0] != 1) ++h1; 
		if(this->casa[1] != 2) ++h1; 
		if(this->casa[2] != 3) ++h1; 
		if(this->casa[3] != 4) ++h1; 
		if(this->casa[4] != 12) ++h1; 
		if(this->casa[5] != 13) ++h1; 
		if(this->casa[6] != 14) ++h1; 
		if(this->casa[7] != 5) ++h1; 
		if(this->casa[8] != 11) ++h1; 
		if(this->casa[9] != 0) ++h1; 
		if(this->casa[10] != 15) ++h1; 
		if(this->casa[11] != 6) ++h1; 
		if(this->casa[12] != 10) ++h1; 
		if(this->casa[13] != 9) ++h1; 
		if(this->casa[14] != 8) ++h1; 
		if(this->casa[15] != 7) ++h1;
	}

	//HEURISTICA 2: ORDEM NUMERICA DAS CASAS
	if(this->heuristica == HEURISTICA_2_ || this->heuristica == HEURISTICA_4_ || this->heuristica == HEURISTICA_5_)
	{
		h2 = 0;

		for(int i = 0; i<15; ++i)
		{
			if((this->casa[caracol[i]] != 0) && (this->casa[caracol[i]] != (this->casa[caracol[i+1]]) -1))
				++h2;
		}
		
	}

	//HEURISTICA 3: DISTANCIA RETANGULAR DA POSICAO IDEAL
	if(this->heuristica == HEURISTICA_3_ || this->heuristica == HEURISTICA_4_ || this->heuristica == HEURISTICA_5_)
	{
		h3 = 0;

		for(int i = 0; i<16; ++i)
		{
			int distancia = i - pos_ideal[this->casa[i]];
			if(distancia < 0) distancia *= -1;

			//deslocamentos horizontais
			h3 += (distancia %4);
			distancia -= (distancia %4);
			//deslocamentos verticais
			while(distancia > 3)
			{
				h3 += 1;
				distancia /= 4;
			}
		}
	}
	
	if(this->heuristica == HEURISTICA_1_)
	{
		this->f = this->g + h1;
		return h1;
	}

	if(this->heuristica == HEURISTICA_2_)
	{
		this->f = this->g + h2;
		return h2;
	}

	if(this->heuristica == HEURISTICA_3_)
	{
		this->f = this->g + h3;
		return h3;
	}

	if(this->heuristica == HEURISTICA_4_)
	{
		h4 = int(PESO_H1_*h1) + int(PESO_H2_*h2) + int(PESO_H3_*h3);
		this->f = this->g + h4;
		return h4;
	}

	if(this->heuristica == HEURISTICA_5_)
	{
		h5 = h3;

		if(h2 > h5)
			h5 = h2;
		if(h1 > h5)
			h5 = h1;

		this->f = this->g + h5;
		return h5;
	}
}

string Tabuleiro::Calcula_ID()
{
	this->id = "";

	for(int i=0; i<16; ++i)
	{
		switch(this->casa[i])
		{
			case 0: this->id += "0"; break;
			case 1: this->id += "1"; break;
			case 2: this->id += "2"; break;
			case 3: this->id += "3"; break;
			case 4: this->id += "4"; break;
			case 5: this->id += "5"; break;
			case 6: this->id += "6"; break;
			case 7: this->id += "7"; break;
			case 8: this->id += "8"; break;
			case 9: this->id += "9"; break;
			case 10: this->id += "10"; break;
			case 11: this->id += "11"; break;
			case 12: this->id += "12"; break;
			case 13: this->id += "13"; break;
			case 14: this->id += "14"; break;
			case 15: this->id += "15"; break;
			default: break;
		}
		if(i%4 == 3)
			this->id += '\n';
		else
			this->id += '\t';
	}

	return this->id;
}

int Tabuleiro::Le_Tabuleiro_STDIN()
{
	int i;

	for(i=0; i<16; ++i)
	{
		cin >> this->casa[i];
		switch(this->casa[i])
		{

			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15: continue;
			default: cout << "ERRO : PECA INVALIDA\n"; return 2;
		}
	}

	if(i != 15)
		return 1;

	return 0;
}

void Tabuleiro::Imprime_Tabuleiro()
{
	cout << "G = " << this->g << ", F = " << this->f << '\n';
	cout << this->id;
}
