void showIdioma(int lang){
	gotoxy(65, 4);printf("Idioma: %s", (lang?"PT":"EN"));
}

void showInsertWordScreen(_word words[], int enWords[], int &size, int lang){
	_word _new;
	do{
		clearCanvas();
		showIdioma(lang);
		printCenter("Inserir palavras", 7);
		gotoxy(2, 9); printf("Português: ");
		gotoxy(42, 9); printf("Inglês: ");
		gotoxy(3, 14); printf("Significado: ");
		
		do{
			readString(_new.pt, 13, 9, 28);
			if(searchWord(words, enWords, size,_new.pt, 1)!= -1){
				showToast("Palavra já cadastrada!", TOAST_WARNING);
			}
		}while(searchWord(words, enWords, size,_new.pt, 1)!= -1);
		removeToast();
		if(stricmp(_new.pt, "\0") == 0)
			return;
		
		do{
			readString(_new.en, 50, 9, 28);
			if(searchWord(words, enWords, size,_new.pt, 0)!= -1){
				showToast("Palavra já cadastrada!", TOAST_WARNING);
			}
		}while(searchWord(words, enWords, size,_new.en, 0)!= -1);
		removeToast();
		if(stricmp(_new.en, "\0") == 0)
			return;
			
		do{
			readString(_new.meaning, 2, 15, 77);
			if(stricmp(_new.meaning, "\0") == 0)
				showToast("Significado vazio!", TOAST_WARNING);
		}while(stricmp(_new.meaning, "\0") == 0);
		removeToast();
		
		if(addWord(words, enWords, size, _new))
			showToast("Cadastrado com sucesso!", TOAST_SUCCESS);
	}while(size < TF && stricmp(_new.pt, "\0") != 0 && stricmp(_new.en, "\0") != 0);
}

void showAlterWordScreen(_word words[], int enWords[], int &size){
	_word _new;
	do{
		clearCanvas();
		printCenter("Inserir palavras", 7);
		gotoxy(10, 9); printf("Português: ");
		gotoxy(50, 9); printf("Inglês: ");
		gotoxy(3, 14); printf("Significado: ");
		
		do{
			readString(_new.pt, 21, 9, 49);
			if(searchWord(words, enWords, size,_new.pt, 1)!= -1){
				showToast("Palavra já cadastrada!");
			}
		}while(searchWord(words, enWords, size,_new.pt, 1)!= -1);
		removeToast();
		if(stricmp(_new.pt, "\0") == 0)
			return;
		
		do{
			readString(_new.en, 58, 9, 79);
			if(searchWord(words, enWords, size,_new.pt, 0)!= -1){
				showToast("Palavra já cadastrada!");
			}
		}while(searchWord(words, enWords, size,_new.en, 0)!= -1);
		removeToast();
		if(stricmp(_new.en, "0") == 0)
			return;
			
		do{
			readString(_new.meaning, 2, 15, 79);
			if(stricmp(_new.meaning, "\0") == 0)
				showToast("Significado vazio!");
		}while(stricmp(_new.meaning, "\0") == 0);
		removeToast();
		
		if(addWord(words, enWords, size, _new))
			showToast("Cadastrado com sucesso!");
	}while(size < TF && stricmp(_new.pt, "\0") != 0 && stricmp(_new.en, "\0") != 0);
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
		do{
			if(searchOther)
				readString(word, 39, 9, 20);
			else{
				gotoxy(39, 9);puts(word);
			}
			int index = searchWord(words, enWords, size, word, lang);
			if(index != -1){
				searchOther = 0;
				removeToast();
				consultMenu = setMenu(11);
			
				addMenuOption(consultMenu, "Mudar Pesquisa");
				addMenuOption(consultMenu, "Ver significado");
				addMenuOption(consultMenu, "Ver tradução");
				addMenuOption(consultMenu, "Alterar");
				addMenuOption(consultMenu, "Excluir");
				
				coord = showMenu(consultMenu);
				
				switch(coord){
					case 0:
						searchOther = 1;
						break;
					case 1:
						clearCoordinates(5, 18, 79, 18);
						gotoxy(5, 18);printf("Significado: %s", words[index].meaning);
						getch();
						break;
					case 2:
						char palavra[50];
						if(!lang)
							strcpy(palavra, words[index].pt);
						else
							clearCoordinates(5, 18, 79, 18);
							strcpy(palavra, words[index].en);
						gotoxy(5, 18);printf("Tradução: %s", palavra);
						getch();
				}
			}else{
				showToast("Palavra não encontrada!", TOAST_ERROR);
			}
			
		}while(searchOther == 0);
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
		gotoxy(10, 13);printf("Tradução:");
		readString(phrase, 2, 10, 78);
		if(stricmp(phrase, "\0") != 0){			
			translatePhrase(words, enWords, size, phrase, lang, translatedPhrase);
			gotoxy(2, 14);puts(translatedPhrase);
			getch();
		}
	}while(stricmp(phrase, "\0") != 0);
}

void showChangeLangScreen(int &lang){
	showIdioma(lang);
	menu langMenu = setMenu(9);
	printCenter("Trocar Idioma", 7);
	addMenuOption(langMenu, "Inglês");
	addMenuOption(langMenu, "Português");
	
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
