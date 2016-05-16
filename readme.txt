#############################################################################

Centro de Tecnologia - Departamento de Informática

Ciência da Computação

6903 - Modelagem e Otimização Algoritmica

Professor Ademir Constantino

#############################################################################

SEGUNDA AVALIAÇÃO: Algoritmo A* aplicado ao problema do tabuleiro de 15 peças

Aluno: Rafael Cortez Sanches

RA: 82357

Maringá, 11 de janeiro de 2016

#############################################################################

##############################################

INSTRUÇÕES PARA COMPILAR E EXECUTAR O PROGRAMA

##############################################


A aplicação está dividida em 3 arquivos de código, os quais estão listados a

seguir:



./include/tabuleiro.h

./tabuleiro.cpp

./main.cpp



COMPILANDO EM LINUX:

*Abrir o terminal
*Mudar o bash para o diretório onde estão os arquivos.

	Ex.: $cd ~/Downloads/trabalho_astar

*Executar o comando "make"

*Se compilado com êxito, o executável "astar_tabuleiro.out" será criado na

	pasta "./bin".

EXECUTANDO EM LINUX:

*Mudar o bash para o diretório "./bin"

*Executar o programa com o seguinte comando:

	$./astar_tabuleiro.out < ARQUIVO_ENTRADA_ --heuristica H --eco

	Sendo ARQUIVO_ENTRADA_ um dentre os 10 arquivos de testes presentes

no diretório "./bin", cujos nomes são "caso1", "caso2", "caso3"...

	H é a heurística a ser utilizada, podendo variar de 1 a 5.
Se o 
parâmetro "--heuristica" for omitido, será usado o valor padrão H = 3.

	O parâmetro "--eco" mostra mensagens informativas sobre o processo

durante a execução, assim como detalhes da solução do caso indicado.



COMPILANDO EM WINDOWS:

*Está disponível um executável já compilado no diretório "./bin". O arquivo

	se chama "astar_tabuleiro.exe"



EXECUTANDO EM WINDOWS:

*Abra o diretório "./bin" no navegador de arquivos do Windows.

*Segurando o botão shift esquerdo, clique com o botão direito na tela.

*No menu, selecione a opção "Abrir janela de comando aqui".

*Execute o programa com o seguinte comando:

	astar_tabuleiro.exe < ARQUIVO_ENTRADA_ --heuristica H --eco

	Sendo ARQUIVO_ENTRADA_ um dentre os 10 arquivos de testes presentes

no diretório "./bin", cujos nomes são "caso1", "caso2", "caso3"...

	H é a heurística a ser utilizada, podendo variar de 1 a 5.
Se o 
parâmetro "--heuristica" for omitido, será usado o valor padrão H = 3.

	O parâmetro "--eco" mostra mensagens informativas sobre o processo

durante a execução, assim como detalhes da solução do caso indicado.


#############################################################################
