void showIdioma(int lang){
	gotoxy(65, 4);printf("Idioma: %s", (lang?"PT":"EN"));
}

void showInsertWordScreen(_word words[], int enWords[], int &size, int lang){
	_word _new;
	do{
		clearCanvas();
		showIdioma(lang);
		printCenter("Inserir palavras", 7);
		gotoxy(2, 9); printf("Portugues: ");
		gotoxy(42, 9); printf("Ingles: ");
		gotoxy(3, 14); printf("Significado: ");
		
		do{
			readString(_new.pt, 13, 9, 28);
			if(searchWord(words, enWords, size,_new.pt, 1)!= -1){
				showToast("Palavra ja cadastrada!", TOAST_WARNING);
			}
		}while(searchWord(words, enWords, size,_new.pt, 1)!= -1);
		removeToast();
		if(stricmp(_new.pt, "\0") ==0)
			return;
			
		int tecla;
		do{
			do{
				readString(_new.en, 50, 9, 28);
				if(searchWord(words, enWords, size,_new.pt, 0)!= -1){
					showToast("Palavra ja cadastrada!", TOAST_WARNING);
				}
			}while(searchWord(words, enWords, size,_new.en, 0)!= -1);
			removeToast();
			if(stricmp(_new.en, "\0") ==0){
				gotoxy(15, 19);printf("Deseja mesmo cancelar? (S/N) ");
				do{
					tecla = readChar(44, 19);
				}while(toupper(tecla) != 'S' && toupper(tecla) != 'N');
				if(toupper(tecla) == 'S')
					return;
			}else
				tecla = 0;
		
			clearCoordinates(15, 19, 46, 19);
		}while(toupper(tecla) == 'N');
		
			
		do{
			readString(_new.meaning, 3, 15, 75);
			if(stricmp(_new.meaning, "\0") == 0)
				showToast("Significado vazio!", TOAST_WARNING);
		}while(stricmp(_new.meaning, "\0") == 0);
		removeToast();
		
		if(addWord(words, enWords, size, _new))
			showToast("Cadastrado com sucesso!", TOAST_SUCCESS);
	}while(size < TF && stricmp(_new.pt, "\0") != 0 && stricmp(_new.en, "\0") != 0);
}

void showAlterWordScreen(_word words[], int enWords[], int &size, int index, int lang){
	_word temp =  lang ? words[index] : words[enWords[index]];
	
	clearCanvas();
	showIdioma(lang);
	printCenter("Alterar palavra", 7);
	gotoxy(2, 9); printf("Portugues: ");
	gotoxy(42, 9); printf("Ingles: ");
	gotoxy(3, 14); printf("Significado: ");
	
	readString(temp.pt, 13, 9, 28, 1);
	readString(temp.en, 50, 9, 28, 1);
	readString(temp.meaning, 3, 15, 75, 1);
	
	if(alterWord(words, enWords, size, temp, index, lang))
		showToast("Alterado com sucesso!", TOAST_SUCCESS);
	clearCanvas();
}

void showExcludeWordScreen(_word words[], int enWords[], int &size, int index, int lang){
	clearCanvas();
	char title [40];
	strcpy(title, "Deseja mesmo remover ");
	strcat(title, lang?words[index].pt : words[enWords[index]].en);
	strcat(title, "?");
	printCenter(title, 9);
	
	menu removeMenu = setMenu(11);
	addMenuOption(removeMenu, "Sim");
	addMenuOption(removeMenu, "Cancelar");
	
	int coord = showMenu(removeMenu);
	
	switch(coord){
		case 0:
			if(excludeWord(words, enWords, size, index, lang))
				showToast("Removido com sucesso");
	}
	
	clearCanvas();
}

void showConsultWordScreen(_word words[], int enWords[], int &size, int lang){
	char word[50];
	int searchOther = 1, coord;
	menu consultMenu;
	
	do{
		clearCanvas();
		showIdioma(lang);
		
		printCenter("Pesquisar", 7);
		
		gotoxy(30, 9); printf("Palavra: ");
		if(searchOther)
			readString(word, 39, 9, 20);
		else{
			gotoxy(39, 9);puts(word);
		}
		int index = searchWord(words, enWords, size, word, lang);
		if(stricmp(word, "\0") !=0){
			if(index != -1){
				searchOther = 0;
				removeToast();
				consultMenu = setMenu(11);
			
				addMenuOption(consultMenu, "Mudar Pesquisa");
				addMenuOption(consultMenu, "Ver significado");
				addMenuOption(consultMenu, "Ver traducao");
				addMenuOption(consultMenu, "Alterar");
				addMenuOption(consultMenu, "Excluir");
				
				coord = showMenu(consultMenu);
				
				switch(coord){
					case 0:
						searchOther = 1;
						break;
					case 1:
						clearCoordinates(5, 18, 79, 18);
						gotoxy(5, 18);printf("Significado: %s", lang ? words[index].meaning : words[enWords[index]].meaning);
						getch();
						break;
					case 2:
						char palavra[50];
						clearCoordinates(5, 18, 79, 18);
						if(!lang)
							strcpy(palavra, words[enWords[index]].pt);
						else
							strcpy(palavra, words[index].en);
						gotoxy(5, 18);printf("Traducao: %s", palavra);
						getch();
						break;
					case 3:
						showAlterWordScreen(words, enWords, size, index, lang);
						break;
					case 4:
						showExcludeWordScreen(words, enWords, size, index, lang);
						break;
				}
			}else{
				showToast("Palavra nao encontrada!", TOAST_ERROR);
				searchOther = 1;
			}
		}else
			return;
	}while(stricmp(word, "\0") != 0);
}

void showTranslateScreen(_word words[], int enWords[], int &size, int lang){

	char phrase[200], translatedPhrase[200];
	do{
		clearCanvas();
		showIdioma(lang);
		printCenter("Traduzir Frases", 7);
		showIdioma(lang);
		gotoxy(65, 5);printf("Trad P: %s", (!lang?"PT":"EN"));
		gotoxy(10, 9);printf("Digite a frase:");
		gotoxy(10, 13);printf("Traducao:");
		readString(phrase, 3, 10, 75);
		if(stricmp(phrase, "\0") != 0){			
			translatePhrase(words, enWords, size, phrase, lang, translatedPhrase);
			gotoxy(3, 14);puts(translatedPhrase);
			getch();
		}
	}while(stricmp(phrase, "\0") != 0);
}

void showChangeLangScreen(int &lang){
	showIdioma(lang);
	menu langMenu = setMenu(9);
	printCenter("Trocar Idioma", 7);
	addMenuOption(langMenu, "Ingles");
	addMenuOption(langMenu, "Portugues");
	
	int coord = showMenu(langMenu);
	
	lang = coord;
}

void generateRelatorio(_word words[], int enWords[], int size){
	FILE *fp;	
	fp = fopen("relatorio.txt" ,"w");
	
	fprintf(fp, "****************PORTUGUÊS****************\n\n");
	for(int i=0; i<size; i++){
		fprintf(fp, "========%s========\n", words[i].pt);
		fprintf(fp, "\tInglês: %s\n", words[i].en);
		fprintf(fp, "\tSignificado: %s\n\n", words[i].meaning);
	}
	fprintf(fp, "****************ENGLISH****************\n\n");
	for(int i=0; i<size; i++){
		fprintf(fp, "========%s========\n", words[enWords[i]].en);
		fprintf(fp, "\tPortuguese: %s\n", words[enWords[i]].pt);
		fprintf(fp, "\tMeaning: %s\n\n", words[enWords[i]].meaning);
	}
	
	fclose(fp);
	
	MessageBeep(MB_OK); // FAZ O WARNING DO SISTEMA
	system("relatorio.txt");
}
