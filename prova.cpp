#include <iostream>
#include <cstdio>
#include <limits>
#include <locale.h>
using namespace std;
int main(){
	FILE *dadosPessoa, *dadosPessoaAux;
	setlocale(LC_ALL, "Portuguese");
	struct pessoa {
		char sexo,fumante;
		int idade;
	};
	struct pessoa pes;
	
	int i, opcaoMenu,fumantes,total,naoFumantes,mulherFumante,totalHomens,totalMulheres;
	float pfum,phnaofum,pmfum;
	char opc;
	do{
		cout << "--------------  MENU  ------------------" << endl << endl;
		cout << "1 - Incluir questionários" << endl;
		cout << "2 - Reiniciar banco de dados" << endl;
		cout << "3 - % total de fumantes" << endl;
		cout << "4 - % de homens não fumantes" << endl;
		cout << "5 - % de mulheres fumantes" << endl;
		cout << "6 - Sair" << endl << endl;
		cout << "----------------------------------------" << endl << endl;
		cout << "Digite a opção desejada: ";
		cin >> opcaoMenu;
		cout << endl << endl;
		system("cls");
		switch (opcaoMenu) {
			case 1:
				cout << "INCLUIR QUESTIONÁRIOS" << endl << endl;
				dadosPessoa = fopen("dadosPessoa.dat", "wb");
				cout << "Deseja cadastrar uma pessoa? (S) ou (N)";
				cin >> opc;
				while (opc == 'S'){
					if (dadosPessoa == NULL){
						cout << "Erro ao abrir o arquivo!";
						cin.ignore();
						cin.get();
					} else {
						cout << "Sexo: (M) ou (F)";
						cin >> pes.sexo;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Idade: ";
						cin >> pes.idade;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Fumante: (S) ou (N)";
						cin >> pes.fumante;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');

						if(fwrite(&pes, sizeof(struct pessoa),1,dadosPessoa) == 1){
							cout << "Cadastro concluído com sucesso" << endl;
							cin.get();
						}
					}
					cout << "Deseja cadastrar mais uma pessoa? (S) ou (N)";
					cin >> opc;
				}
				fclose(dadosPessoa);
				cin.get();
				break;
			case 2:
				cout << "REINICIAR BANCO DE DADOS" << endl;
				dadosPessoaAux = fopen("dadosPessoa.aux","wb");
				dadosPessoa = fopen("dadosPessoa.dat","rb");
				while (!feof(dadosPessoa)){
					fwrite (&pes, sizeof(struct pessoa),1,dadosPessoaAux);
					fread (&pes, sizeof(struct pessoa),1,dadosPessoa);
				}
				fclose(dadosPessoaAux);
				fclose(dadosPessoa);
				remove("dadosPessoa.dat");
				rename("dadosPessoa.aux","dadosPessoa.dat");
				cout << "Banco reiniciado com sucesso" << endl;
				break;
			case 3:
				cout << "% TOTAL DE FUMANTES" << endl << endl;
				dadosPessoa = fopen("dadosPessoa.dat","rb");
				fread (&pes, sizeof(struct pessoa),1, dadosPessoa);
				total = 0;
				fumantes = 0;
				while (!feof(dadosPessoa)){
					total++;
					if(pes.fumante == 'S'){
						fumantes++;
					}
					fread (&pes, sizeof(struct pessoa),1, dadosPessoa);
				}
				pfum = (fumantes*100)/total;
				cout << "Total de entrevistados: " << total << endl;
				cout << "Total de fumantes: " << pfum << "%" << endl;
				fclose(dadosPessoa);
				cin.get();
				break;	
			case 4:
				cout << "% DE HOMENS NÃO FUMANTES" << endl;
				dadosPessoa = fopen("dadosPessoa.dat","rb");
				fread (&pes, sizeof(struct pessoa),1, dadosPessoa);
				totalHomens = 0;
				naoFumantes = 0;
				while (!feof(dadosPessoa)){
					if(pes.sexo == 'M'){
						totalHomens++;
					}
					if(pes.fumante == 'N'){
						if(pes.idade < 40){
							naoFumantes++;
						}
					}
					fread (&pes, sizeof(struct pessoa),1, dadosPessoa);
				}
				phnaofum = (naoFumantes/totalHomens)*100;
				cout << "Total de homens entrevistados: " << totalHomens << endl;
				cout << "Total de homens não fumantes abaixo de 40 anos: " << phnaofum << "%" << endl;
				fclose(dadosPessoa);
				cin.get();
				break;
			case 5:
				cout << "% DE MULHERES FUMANTES" << endl;
				dadosPessoa = fopen("dadosPessoa.dat","rb");
				fread (&pes, sizeof(struct pessoa),1, dadosPessoa);
				totalMulheres = 0;
				mulherFumante = 0;
				while (!feof(dadosPessoa)){
					if(pes.sexo == 'M'){
						totalMulheres++;
					}
					if(pes.fumante == 'S'){
						if(pes.idade < 40){
							mulherFumante++;
						}
					}
					fread (&pes, sizeof(struct pessoa),1, dadosPessoa);
				}
				pmfum = (mulherFumante/totalMulheres)*100;
				cout << "Total de mulheres entrevistadas: " << totalMulheres << endl;
				cout << "Total de mulheres fumantes acima de 40 anos: " << pmfum << "%" << endl;
				fclose(dadosPessoa);
				cin.get();
				break;
		}
		system("cls");
	} while (opcaoMenu != 6);
}
