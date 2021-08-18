#include <clocale>
#include <fstream>
#include <iostream>

#include "Movie.h"

int main(int argc, char* argv[]) { //
	// int argc � a quantidade de argumentos passados para a main via linha de comando
	// char& argv � um array de char* que cont�m os parametros passados na linha de comando

	//if (argc < 2) {
		// quando � igual a 1, significa que n�o foi passado nenhum parametro, apenas o arquivo executavel
	//	cout << "Uso: \n" << argv[0] << " <arquivo>\n";

	//	return 1;
	//}

	setlocale(LC_CTYPE, "pt_BR");

	Movie* movies = nullptr;
	int movieCount = 0;

	ifstream ifs("imdb.txt");
	
	//l� se o arquivo estiver aberto
	if (ifs.is_open()) {
		string data;

		//l� a 1� linha do arquivo e salva na vari�vel data
		getline(ifs, data);

		// tenta converter string para int
		// caso n�o consiga, stoi lan�a uma exce��o no catch()
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

		//inicia quando a quantidade de filmes informada � menor do que os dados dos filmes existentes
		while (!ifs.eof() && counter < movieCount) {
			getline(ifs, data);
			if (data.empty()) {
				cout << "Erro ao ler o nome do filme na posi��o " << (counter + 1) << "(dado vazio). O nome do filme passa a ser ???...\n";
				data = "???";
			}

			//salva o nome do filme em um objeto Movie
			movies[counter].setTitle(data);

			//l� prox linha (ano de lan�amento) e converte em int
			getline(ifs, data);

			try{
				year = stoi(data);
			}
			catch (invalid_argument e){
				std::cout << "Erro ao ler o ano do filme '" << movies[counter].getTitle() << "'. O ano do lan�amento passa a ser -1...\n";
				year = -1;
			}

			//salva o ano do filme em um objeto Movie
			movies[counter].setYear(year);

			//l� prox linha (nota) e converte em float
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

	// A vari�vel movie � um ponteiro para Movie e aponta para a vari�vel movies.
	// Ao fazer isso, o valor de movie � o endere�o de mem�ria de movies.
	// Como movies � um array din�mico, o endere�o inicial de movies (e, consequentemente, de movie) aponta para o primeiro elemento do array.
	// ^^^ Na verdade, um array � um ponteiro. Sendo assim, o nome da vari�vel de um array � um ponteiro que aponta para o primeiro elemento do array.

	Movie* movie = movies;

	for (int i = 0; i < movieCount; ++i)
	{
		std::cout << movie->getTitle() << " (" << movie->getYear() << ") " << movie->getScore() << '\n';

		// Por ser um ponteiro que inicialmente aponta para o primeiro elemento de um array, o incremento significa
		// que estamos avan�ando para o pr�ximo elemento do array.
		// Perceba que, ao final do loop for, o valor de movie j� n�o aponta mais para o primeiro elemento do array movies.
		*(movie++);
	}

	// O c�digo acima, sem movie, equivale �:
	//for (int i = 0; i < movieCount; ++i)
	//{
	//	std::cout << movies[i].GetTitle() << " (" << movies[i].GetYear() << ") " << movies[i].GetScore() << '\n';
	//}

	// N�o podemos esquecer de liberar a mem�ria que foi alocada dinamicamente.
	delete[] movies;
	movies = nullptr;

	// Se n�o inclu�rmos esse return 0;, n�o tem problema, pois se chegamos no final da main(),
	// o programa ter� um return 0; impl�cito.
	return 0;

}
	