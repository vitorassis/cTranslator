#include <stdio.h>
#include "interio/interio.h"

#define TF 300

#include "words.cpp"
#include "interface.cpp"

int main(void){
	setCanvas('.', 1, 1, 10);
	showTitle("Tradutor", 3);
	
	_word words[TF];
	int enWords[TF], size=0, coord, lang=1;
	
	int enableIn, enableOut;
	
	menu mainMenu = setMenu(9);
	
	do{
		drawCanvas();
		printCenter("Menu", 7);
		clearMenuOptions(mainMenu);
		
		if(size == 0){
			enableIn = 1;
			enableOut = 0;
		}else if(size < TF){
			enableIn = 1;
			enableOut = 1;
		}else{
			enableIn = 0;
			enableOut = 0;
		}
		
		addMenuOption(mainMenu, "Inserir palavras", enableIn);
		addMenuOption(mainMenu, "Consultar palavras", enableOut);
		addMenuOption(mainMenu, "Gerar relatorio", enableOut);
		addMenuOption(mainMenu, "Trocar idioma");
		addMenuOption(mainMenu, "Traduzir frase", enableOut);
		addMenuOption(mainMenu, "Sair");
		
		showIdioma(lang);
		
		coord = showMenu(mainMenu);
		clearCanvas();
		
		switch(coord){
			case 0:
				showInsertWordScreen(words, enWords, size, lang);
				break;
			case 1:
				showConsultWordScreen(words, enWords, size, lang);
				break;
			case 2:
				generateRelatorio(words, enWords, size);
				break;
			case 3:
				showChangeLangScreen(lang);
				break;
			case 4:
				showTranslateScreen(words, enWords, size, lang);
				break;
		}
		clearCanvas();
		removeToast();
	}while(coord != 5);
}
