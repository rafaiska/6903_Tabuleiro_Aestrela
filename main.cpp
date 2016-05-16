#include <tabuleiro.h>
#include <map>
#include <queue>
#include <ctime>
#include <cstring>
#include <cstdlib>
using namespace std;

bool ECO;
int HEURISTICA;

int main(int argc, char *argv[])
{
	//Parametros padrao de execucao
	ECO = false;
	HEURISTICA = 3;
	//Identificacao dos parametros
	for(int i=0; i<argc; ++i)
	{
		if(!strcmp(argv[i],"--eco"))
			ECO = true;
		else if(!strcmp(argv[i],"--heuristica") && (i+1 < argc))
			HEURISTICA = atoi(argv[i+1]);
	}
	//Numero de iteracoes
	int iteracoes = 0;
	//Numero de redundancias tratadas
	int redundancia = 0;
	//Marcadores de tempo
	time_t tempo_inicial;
	time_t tempo_decorrido;
	//CONJUNTOS UTILIZADOS NO PROBLEMA:
	//Foram usados dicionarios para consulta rapida (ANSI C++ implementa-os como arvore binaria de busca)
	map <string, Tabuleiro> A;
	map <string, Tabuleiro> F;
	//PQueue eh uma fila de prioridade, usada para consultar no de menor f() do conjunto A
	priority_queue <Tabuleiro> PQueue;
	//Estados inicial e final do problema
	Tabuleiro inicial;
	Tabuleiro destino;

	destino.Set_G(-1);

	//Construcao do tabuleiro inicial do problema
	inicial.Le_Tabuleiro_STDIN();
	inicial.Calcula_ID();
	inicial.SetHeuristica(HEURISTICA -1);
	inicial.Calcula_H();
	inicial.Set_P("###Inicio###\n");

	//Insere tabuleiro inicial no conjunto A
	A[inicial.Get_ID()] = inicial;
	PQueue.push(inicial);

	tempo_inicial = time(NULL);

	//Laco principal
	while(!A.empty() && destino.Get_G() == -1)
	{
		Tabuleiro atual;
		vector <Tabuleiro> sucessores;

		++iteracoes;

		//Remove redundancias de PQueue
		while(A.find(PQueue.top().Get_ID()) == A.end())
		{
			PQueue.pop();
			++redundancia;
		}

		//Remove no de f() minimo de A, insere-o em F
		atual = PQueue.top();
		PQueue.pop();
		F[atual.Get_ID()] = atual;
		A.erase(atual.Get_ID());

		if(ECO == true && iteracoes % 10000 == 0)
		{
			tempo_decorrido = time(NULL) - tempo_inicial;
			cout << "##################\n";
			cout << iteracoes << " iteracoes ate o momento.\n";
			cout << A.size() << " elementos em A.\n";
			cout << F.size() << " elementos em F.\n";
			cout << PQueue.size() << " elementos no heap.\n";
			cout << "Ultimo valor de f(): " << atual.Get_F() << '\n';
			cout << "Tempo de processamento: " << tempo_decorrido/3600 << "h " << tempo_decorrido/60 << "m " << tempo_decorrido % 60 << "s\n";
			cout << "Redundancias tratadas: " << redundancia << '\n';
		}

		//Gera sucessores do no removido e verifica se ha nos redundantes
		atual.Gerar_Vizinhos(sucessores);
		for(int i =0; i<sucessores.size(); ++i)
		{
			map <string,Tabuleiro>::iterator it;
			//Esta no estado final do problema
			if(sucessores[i].Get_H() == 0)
			{
				destino = sucessores[i];
				break;
			}
			//Esta em A
			else if((it = A.find(sucessores[i].Get_ID())) != A.end())
			{
				if((it->second).Get_G() > sucessores[i].Get_G())
				{
					(it->second) = sucessores[i];
					PQueue.push(sucessores[i]);
				}
			}

			//Esta em F 
			else if((it = F.find(sucessores[i].Get_ID())) != F.end())
			{
				if((it->second).Get_G() > sucessores[i].Get_G())
				{
					F.erase(it);
					A[sucessores[i].Get_ID()] = sucessores[i];
					PQueue.push(sucessores[i]);
				}
			}
			
			//Nao esta nem em A nem em F
			else
			{
				A[sucessores[i].Get_ID()] = sucessores[i];
				PQueue.push(sucessores[i]);
			}
		}
		
	}
	//Encontrou solucao
	if(destino.Get_G() != -1)
	{
		tempo_decorrido = time(NULL) - tempo_inicial;
		vector <Tabuleiro> solucao;
		solucao.push_back(destino);

		while(solucao[0].Get_ID() != inicial.Get_ID())
		{
			map <string,Tabuleiro>::iterator it;

			if((it = A.find(solucao[0].Get_P())) != A.end())
				solucao.insert(solucao.begin(), it->second);
			else if((it = F.find(solucao[0].Get_P())) != F.end())
				solucao.insert(solucao.begin(), it->second);
			else
				break;
		}

		cout << (solucao.size() -1);
		if(ECO == true)
		{
			cout << '\n';
			for(int i=0; i<solucao.size(); ++i)solucao[i].Imprime_Tabuleiro();
			cout << "Tempo total de execucao: " << tempo_decorrido/3600 << "h " << tempo_decorrido/60 << "m " << tempo_decorrido % 60 << "s\n";
		}
	}
	else
	{
		cout << "ERRO: NAO ENCONTROU SOLUCAO VALIDA\n";
		return 1;
	}

	return 0;
}
