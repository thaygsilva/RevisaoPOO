#include <clocale>
#include <fstream>
#include <iostream>

#include "Movie.h"

int main(int argc, char* argv[]) { //
	// int argc é a quantidade de argumentos passados para a main via linha de comando
	// char& argv é um array de char* que contém os parametros passados na linha de comando

	//if (argc < 2) {
		// quando é igual a 1, significa que não foi passado nenhum parametro, apenas o arquivo executavel
	//	cout << "Uso: \n" << argv[0] << " <arquivo>\n";

	//	return 1;
	//}

	setlocale(LC_CTYPE, "pt_BR");

	Movie* movies = nullptr;
	int movieCount = 0;

	ifstream ifs("imdb.txt");
	
	//lê se o arquivo estiver aberto
	if (ifs.is_open()) {
		string data;

		//lê a 1ª linha do arquivo e salva na variável data
		getline(ifs, data);

		// tenta converter string para int
		// caso não consiga, stoi lança uma exceção no catch()
		try {
			movieCount = stoi(data);
		}
		catch(invalid_argument e){
			cout << "Erro ao ler quantidade de filmes... Fechando." << endl;

			ifs.close();
			return 2;
		}

		//criando array com os dados do filme
		movies = new Movie[movieCount];

		int year = 0;
		float score = 0.0f;
		int counter = 0;

		//inicia quando a quantidade de filmes informada é menor do que os dados dos filmes existentes
		while (!ifs.eof() && counter < movieCount) {
			getline(ifs, data);
			if (data.empty()) {
				cout << "Erro ao ler o nome do filme na posição " << (counter + 1) << "(dado vazio). O nome do filme passa a ser ???...\n";
				data = "???";
			}

			//salva o nome do filme em um objeto Movie
			movies[counter].setTitle(data);

			//lê prox linha (ano de lançamento) e converte em int
			getline(ifs, data);

			try{
				year = stoi(data);
			}
			catch (invalid_argument e){
				std::cout << "Erro ao ler o ano do filme '" << movies[counter].getTitle() << "'. O ano do lançamento passa a ser -1...\n";
				year = -1;
			}

			//salva o ano do filme em um objeto Movie
			movies[counter].setYear(year);

			//lê prox linha (nota) e converte em float
			getline(ifs, data);

			try{
				score = stof(data);
			}
			catch (std::invalid_argument e){
				std::cout << "Erro ao ler a nota do filme '" << movies[counter].getTitle() << "'. A nota do filme passa a ser -1...\n";
				score = -1.0f;
			}

			movies[counter].setScore(score);

			++counter;
		}
		if (counter < movieCount) {
			cout << "Quantidade de filmes esperada: " << movieCount << " (obteve: " << counter << ").\n";
			movieCount = counter;
		}

		//fechar arquivo
		ifs.close();
	}else{ // if (ifs.is_open())
		cout << "Erro ao abrir o arquivo de dados. Encerrando...\n";
		return 3;
	}

	cout << "=== TOP-" << movieCount << " FILMES (de acordo com o IMDb) ===\n";

	// A variável movie é um ponteiro para Movie e aponta para a variável movies.
	// Ao fazer isso, o valor de movie é o endereço de memória de movies.
	// Como movies é um array dinâmico, o endereço inicial de movies (e, consequentemente, de movie) aponta para o primeiro elemento do array.
	// ^^^ Na verdade, um array é um ponteiro. Sendo assim, o nome da variável de um array é um ponteiro que aponta para o primeiro elemento do array.

	Movie* movie = movies;

	for (int i = 0; i < movieCount; ++i)
	{
		std::cout << movie->getTitle() << " (" << movie->getYear() << ") " << movie->getScore() << '\n';

		// Por ser um ponteiro que inicialmente aponta para o primeiro elemento de um array, o incremento significa
		// que estamos avançando para o próximo elemento do array.
		// Perceba que, ao final do loop for, o valor de movie já não aponta mais para o primeiro elemento do array movies.
		*(movie++);
	}

	// O código acima, sem movie, equivale à:
	//for (int i = 0; i < movieCount; ++i)
	//{
	//	std::cout << movies[i].GetTitle() << " (" << movies[i].GetYear() << ") " << movies[i].GetScore() << '\n';
	//}

	// Não podemos esquecer de liberar a memória que foi alocada dinamicamente.
	delete[] movies;
	movies = nullptr;

	// Se não incluírmos esse return 0;, não tem problema, pois se chegamos no final da main(),
	// o programa terá um return 0; implícito.
	return 0;

}
	