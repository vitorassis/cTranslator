struct _word{
	char pt[50];
	char en[50];
	char meaning[150];
	int active;
};

void ordenateWords(_word words[], int enWords[], int &size){
	int indexMaior, j, _aux;
	_word aux;
	
	for(int i=1; i<size; i++)
		for(j=0; j<size-i; j++){
			if(stricmp(words[j].pt, words[j+1].pt) > 0){
				aux = words[j];
				words[j] = words[j+1];
				words[j+1] = aux;
			}
		}
	
	for(int i=0; i<size; i++)
		enWords[i] = i;
	
	for(int i=1; i<size; i++)
		for(j=0; j<size-i; j++){
			if(stricmp(words[enWords[j]].en, words[enWords[j+1]].en) > 0){
				_aux = enWords[j];
				enWords[j] = enWords[j+1];
				enWords[j+1] = _aux;
			}
		}
}

int addWord(_word words[], int enWords[], int &size, _word new_word){
	new_word.active = 1;
	words[size] = new_word;
	size++;
	ordenateWords(words, enWords, size);
	return 1;
}

int searchWord(_word words[], int enWords[], int size, char word[], int lang){
	int i=0, f=size-1, meio=0;
	if(lang == 1){
		while(i<=f && stricmp(words[meio].pt, word) != 0){
			meio = (i+f)/2;
			
			if(stricmp(word, words[meio].pt) > 0)
				i = meio+1;
			else if(stricmp(word, words[meio].pt) < 0)
				f = meio-1;
		}
	}else{
		while(i<=f && stricmp(words[enWords[meio]].en, word) != 0){
			meio = (i+f)/2;
			
			if(stricmp(word, words[enWords[meio]].en) > 0)
				i = meio+1;
			else if(stricmp(word, words[enWords[meio]].en) < 0)
				f = meio-1;
		}
	}
	if(i <= f)
		return meio;
	else
		return -1;
}

void searchSubWords(_word words[], int enWords[], char word[], int size, int indexes[], int &indexes_size, char notFound[][50], int lang){
	indexes_size=0;
	int i=0, len=strlen(word), index, last_i=0;
	char subWord[50];
	int subWordLen;
	int notFoundLen = 1;
	strcpy(notFound[0], "1");
	for(i=last_i; i<len; i=last_i){
		strcpy(subWord, "\0");
		subWordLen = 0;
		index = -1;
		for(int j=i; j<len; j++){
			subWord[subWordLen++] = word[j];
			subWord[subWordLen] = '\0';	
			int _index = searchWord(words, enWords, size, subWord, lang);
			if(_index != -1){
				index = _index;
				last_i = j+1;
			}
		}
		if(index != -1)
			indexes[indexes_size] = index;
		else{
			strcpy(notFound[notFoundLen], subWord);
			indexes[indexes_size] = notFoundLen *-1;
			last_i = len;
		}
		indexes_size++;			
	}
}

void translatePhrase(_word words[], int enWords[], int size, char phrase[], int lang, char translatedPhrase[]){
	int translateTo = lang^1;
	char splitWords[50][50];
	int len = strlen(phrase);
	strcpy(translatedPhrase, "\0");
	
	int wordsQtd=0;
	int wordSize=0;
	
	for(int i=0; i<len; i++){
		if(phrase[i] != ' '){
			splitWords[wordsQtd][wordSize++] = phrase[i];
			splitWords[wordsQtd][wordSize] = '\0';
		}else{
			wordsQtd++;
			wordSize=0;
		}
	}
	wordsQtd++;
	
	int indexes[200];
	char notFound[200][50];
	int size_indexes;
	
	char translatedWord[50];
	
	for(int i=0; i<wordsQtd; i++){
		searchSubWords(words, enWords, splitWords[i], size, indexes, size_indexes, notFound, lang);
		for(int j=0; j<size_indexes; j++){
			if(indexes[j] >= 0){
				if(translateTo == 1){
					strcpy(translatedWord, words[indexes[j]].pt);
				}else{
					strcpy(translatedWord, words[indexes[j]].en);
				}
			}else{
				strcpy(translatedWord, notFound[indexes[j] *-1]);
			}
			strcat(translatedWord, " ");
			strcat(translatedPhrase, translatedWord);
		}
	}
}

int alterWord(_word words[], int enWords[], int &size, _word temp, int index, int lang){
	if(lang)
		words[index] = temp;	
	else
		words[enWords[index]] = temp;
	ordenateWords(words, enWords, size);
	return 1;
}
