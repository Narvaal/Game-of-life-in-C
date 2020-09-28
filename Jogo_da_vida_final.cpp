#include<stdio.h>
#include <time.h> 
#include <windows.h>

/*
			Regras do jogo
	For a space that is 'populated':
	    Each cell with one or no neighbors dies, as if by solitude. 
	    Each cell with four or more neighbors dies, as if by overpopulation. 
	    Each cell with two or three neighbors survives. 
	For a space that is 'empty' or 'unpopulated'
	    Each cell with three neighbors becomes populated. 
*/


// Definir o tamanho da matriz
int altura = 20;
int largura = 20;
int mat[20][20];

//para mudar o tamanho da matriz é necessario mudar os 4 campos
/*
	// Exemplo de matriz 10x10
	int altura = 10;
	int largura = 10;
	int mat[10][10];
*/


//Var para mudar a velociadade da execução
float velocidade = 0.5;



void tamanho_tela(){
  system("mode 60,20");
  /*
  Para que tamanho da tela sejá igual ao da matriz 
  é necessario mudar  a linha acima.
  
  system("mode (numero de linhas *3) , (numero de colunas)")
  
  Exemplo de matriz 10x10
  system("mode 30,10);
 */ 
  SMALL_RECT WinRect = {0,0, 500, 500};   
  SMALL_RECT* WinSize = &WinRect;
  SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   
}


// func para transformar todos os valores da matriz em 0
void init_mat(){
	for(int i=0;i < altura; i++){
		for(int j=0; j < largura; j++){
			mat[i][j] = 0;		
		}
	}
}

//func para limpar a tela no win
void clean(){
	system("cls");
}


// func para delay na tela, serve para deixa o programa mais visível para user 
void delay(float number_of_seconds) 
{ 
    float milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds); 
} 

void Escr_col(float dcor,int dtela){
	
	for(int i=0;i < dtela; i++){
		system("color 0");
		delay(dcor);
		system("color 1");
		delay(dcor);
		system("color 3");
		delay(dcor);
		system("color 4");
		delay(dcor);
		system("color 5");
		delay(dcor);
		system("color 6");
		delay(dcor);
		system("color 7");
		delay(dcor);
	}
}

// add um ponto na matriz, pontos na matriz são reprensados por valores maiors que 0
void add_p(int x,int y){
	mat[x][y] = 1;
}



// func para imprimir a matriz com valores
void imprime_mat_valor(){
	printf("\n");
	for(int i=0;i < altura; i++){
		for(int j=0; j < largura; j++){
			printf("%i ",mat[i][j]);
		}
		printf("\n");
	}
}


// func para imprimir a matriz com caracteres
void imprime_mat(){
	printf("\n");
	for(int i=0;i < altura; i++){
		for(int j=0; j < largura; j++){
			if(mat[i][j] >= 1){
				printf(" O ");
			}else{
				printf(" . ");
			}
		}
		printf("\n");
	}
}

// Executa todas as regras do jogo e exibe na tela 
void regras(){
	int proxima = 0; // serve para contar quantos celulas proximas exitem 
	for(int i=0;i < altura; i++){
		for(int j=0; j < largura; j++){	
		
			// percorre toda a matriz
			
			if(mat[i][j] == 1){ //Se o elemento em questão for 1
				proxima = 0; //zera o proxima porque estamos em um loop
				
				/*
					Os testes abaixo testam se o valor 
					dos(*) em volta da celula analizada 
					é igual a 1 ou igual a -1
					
					Representação:
					
						  		*
						  		
					  		* celula *
					  		
						 		*
					
					Se algum desses valres for igual a 1 
					ou igual a -1 a var proxima vai ser 
					incrementada
				*/
				if(mat[i-1][j] == 1 ||  mat[i-1][j] == -1){
					proxima++;
				}
				if(mat[i][j-1] == 1 ||  mat[i][j-1] == -1){
					proxima++;
				}
				if(mat[i][j+1] == 1 ||  mat[i][j+1] == -1){
					proxima++;
				}
				if(mat[i+1][j] == 1 ||  mat[i+1][j] == -1){
					proxima++;
				}
				
				/*	
					O codigo abaixo faz a mesma coisa 
					que o exemplo de cima mas com as 
					diagonais
					
					Representação:
					
						  	*	   *
						  	
					  		 celula 
					  		 
						 	*      *
					
					Se algum desses valores forem igual 
					a 1 ou igual a -1 proxima vai ser 
					incrementada
				*/
				

				if(mat[i-1][j-1] == 1 ||  mat[i-1][j-1] == -1){
					proxima++;
				}
				if(mat[i+1][j+1] == 1 || mat[i+1][j+1] == -1){
					proxima++;
				}
				if(mat[i+1][j-1] == 1 ||  mat[i+1][j-1] == -1){
					proxima++;
				}
				if(mat[i-1][j+1] == 1 ||  mat[i-1][j+1] == -1){
					proxima++;
				}
				/* 
					Se a var proxima for igual a um 
					numero <= 1 a celula vai ser apagada 
					por causa da lei da solidão
					
					Se a var proxima for igual a um 
					numero >= 4 a celula vai ser apagada 
					por causa da lei da super população
					
				*/
				if(proxima <= 1 || proxima >= 4){
					mat[i][j] = -1;
		
				}    
			}	
		}
	}

	for(int i=0;i < altura; i++){
		for(int j=0; j < largura; j++){
			
			// percorre toda a matriz
		
			if(mat[i][j] == 0){// Se o elemento em questão for 0
				proxima = 0; // proxima = 0;
				
				
				// Testa quantos 1's e -1's existem ao redor do local atual da matriz:
				if(mat[i-1][j] == 1 ||  mat[i-1][j] == -1){
					proxima++;
				}
				if(mat[i][j-1] == 1 ||  mat[i][j-1] == -1){
					proxima++;
				}
				if(mat[i][j+1] == 1 ||  mat[i][j+1] == -1){
					proxima++;
				}
				if(mat[i+1][j] == 1 ||  mat[i+1][j] == -1){
					proxima++;
				}
				if(mat[i-1][j-1] == 1 ||  mat[i-1][j-1] == -1){
					proxima++;
				}
				if(mat[i+1][j+1] == 1 || mat[i+1][j+1] == -1){
					proxima++;
				}
				if(mat[i+1][j-1] == 1 ||  mat[i+1][j-1] == -1){
					proxima++;
				}
				if(mat[i-1][j+1] == 1 ||  mat[i-1][j+1] == -1){
					proxima++;
				}
				
				/*
					Os testes acima fazem o mesmo processo
					testam  se os valores em volta são
					iguais a 1 or
					
					Representação:
					
						*     *    *
						  	
					  	*  celula  *
					  		 
					    *     *    *
					    
				*/
				// Caso haja 3 adjacentes, sera trocado o valor deste espaco para 2
				if(proxima == 3){
					mat[i][j] = 2;
		
		
					}
				}
			}
		}
		
		//Imprime os valores da matriz na tela
		imprime_mat();
		
		//adiona um delay 
		delay(velocidade);
		
		//limpa a tela
		clean();
		
		
		
		
		for(int i=0;i < altura; i++){
			for(int j=0; j < largura; j++){
				//percorre tdos os elementos da matriz
			
			
				/* 
					se o elemento for igual a -1  ele é igual a zero
					o elemento é igual a -1 porque cada celula é 
				 	independênte e as vezes as celulas precisam fazer 
				 	duas operações ao mesmo tempo e por isso precisam 
				 	saber onde uma celula foi apagada 
		 		*/
				if(mat[i][j] == -1){
					mat[i][j] = 0; // celulas -1 são iguas a 0 depois do ciclo
				}
				/* 
					celulas iguais a 2 siginificam que ela já foi 
					computada e atualizada e dado isso ela não é
					mais alterada. Depois do ciclo a ceula é igual
					a 1 siginificam que ele pode ser atualizada 
					agora
		 		*/
				
				if(mat[i][j] == 2){
					mat[i][j] = 1; // celulas 2 são iguas a 1 depois do ciclo
				}
			}
		}
	}

// func para imprimir o menu
int menu_p(){
	int esc = 0;
	
	system("color 0F");
	system("title Jogo da vida");
	system("mode 50,32");
	printf("__________________________________________________");
	printf("\n\n");
	printf("                  Menu de exemplos                ");
	printf("__________________________________________________");
	printf("--------------------------------------------------");
	printf("\n\n[1] - Morte por solidao\n\n\n");
	printf("[2] - Small Exploder\n\n\n");
	printf("[3] - Glider\n\n\n");
	printf("[4] - 7-Line\n\n\n");
	printf("[5] - Crosshair generator\n\n\n");
	printf("[6] - Creditos\n\n\n");
	printf("[0] - Sair\n\n\n");
	
	
	printf("Escolha uma opc-----------------------------------\n\n-> ");
	scanf("%d",&esc);
	
	return esc;
}	


// cada escolha do menu  é uma func 
void esc1(){
	system("title Simulacão_01");
	init_mat();//zera a matriz
	tamanho_tela();// define o tamanho da tela
	
	// adiciona os pontos 1 na matriz
	add_p(4,5);
  	// representa as cordenadas: add_p(x,y);
  
	add_p(4,8);
	add_p(2,5);
	add_p(5,8);
	add_p(6,5);
	
	//imprime a matriz
	imprime_mat();
	
	//delay de 3 segundos para o user visualizar a matriz inicial
	delay(3);
	
	//executa o jogo
	//para que o programa execute varais vezes é necessario um for com um limite
	for(int i = 0; i < 10;i++){ 
		regras();	
	}	
}

//As 3 func abaixo seguem o mesmo exemplo que a de cima mas com pontos diferentes
//O for de cada esc é diferente pois alguns exemplos executam por mais tempo na tela
void esc2(){
	system("title Simulacão_02");
	init_mat();
	tamanho_tela();
	
	add_p(10,8);
	add_p(11,8);
	add_p(10,9);
	add_p(10,10);
	add_p(11,10);
	add_p(9,9);
	add_p(12,9);
	imprime_mat();
	delay(3);
	for(int i = 0; i < 20;i++){
		regras();	
	}
}

void esc3(){
	system("title Simulacão_03");
	init_mat();
	tamanho_tela();
	
	add_p(4,4);
	add_p(4,5);
	add_p(4,6);
	add_p(3,6);
	add_p(2,5);
	
	imprime_mat();
	delay(3);
	for(int i = 0; i < 30;i++){
		regras();	
	}	
}

void esc4(){
	system("title Simulacão_04");
	init_mat();
	tamanho_tela();
	
	add_p(10,6);
	add_p(10,7);
	add_p(10,8);
	add_p(10,9);
	add_p(10,10);
	add_p(10,11);
	add_p(10,12);
	
	imprime_mat();
	delay(3);
	
	for(int i = 0; i < 30;i++){
		regras();	
	}
}

void esc6(){
	system("title Simulação_05");
	init_mat();
	tamanho_tela();
	
	add_p(10,11);
    add_p(10,12);
    add_p(10,13);
    add_p(10,14);
    add_p(10,15);
    add_p(10,16);
    add_p(10,17);
    add_p(8,12);
    add_p(8,13);
    add_p(8,14);
    add_p(8,15);
    add_p(8,16);
    add_p(12,12);
    add_p(12,13);
    add_p(12,14);
    add_p(12,15);
    add_p(12,16);
    add_p(14,13);
    add_p(14,14);
    add_p(14,15);
    add_p(6,13);
    add_p(6,14);
    add_p(6,15);
    
    imprime_mat();
	delay(3);
	
	for(int i = 0; i < 30;i++){
		regras();	
	}
}

void esc5(){
	system("title Creditos");
	system("mode 50,13");
	

	printf("__________________________________________________\n");
	printf("\n                     Creditos\n");
	printf("__________________________________________________\n\n\n");
		 
	printf("               Escrito por Alesssandro \n                      Bezerra\n");
	printf("                         e \n                   Renan Okamoto");
	Escr_col(0.2,3);
	
	
}




int main(){
	int esc = 0;
	system("title Jogo da vida");
	tamanho_tela();
	
	//loop prin 
	for(;;){
		// func esc retorna o valor que o user escolheu 
		esc = menu_p();
		if(esc == 1){
			esc1();
		}
		else if(esc == 2){
			esc2();
		}
		else if(esc == 3){
			esc3();
		}
		else if(esc == 4){
			esc4();
		}
		else if(esc == 5){
			esc6();
		}
		else if(esc == 6){
			esc5();
		}
		else if(esc == 0){
			clean();
			printf("Apple me contrata!");
			return 0;
		}
	}
}
