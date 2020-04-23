//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
//DEFINES
#define ERROR_OPEN_FILE -3
#define MAX_NUMBER_OF_SYMBOLS_IN_STRING 255
#define MAX_ARR 10
//FUNCTIONS_PROTOTYPES
char* deletePunctuationMark(const char* symbol);
char* toLowerCase(char* str, char* strToLower);

struct WordCounter
{
	char* word;
	int count;
};


int main()
{
	FILE* filePointer = NULL;
	FILE* toWriteWithoutPunctuation = NULL;
	FILE* toWriteInLowerCase = NULL;
	FILE* readFromFileWithoutPunctuation = NULL;
	FILE* countedWords = NULL;
	filePointer = fopen("Text1.txt", "r");
	toWriteWithoutPunctuation = fopen("WithoutPunctuation.txt", "w+");
	readFromFileWithoutPunctuation = fopen("WithoutPunctuation.txt", "r");
	toWriteInLowerCase = fopen("InLowerCase.txt", "w+");
	countedWords = fopen("Result.txt", "w+");



	if (filePointer == NULL) {
		printf("error opening file");
		getchar();
		exit(ERROR_OPEN_FILE);
	}

	if ((filePointer != NULL) && (toWriteWithoutPunctuation != NULL)) {

		char* stringFromFile = (char*)malloc(MAX_NUMBER_OF_SYMBOLS_IN_STRING);

		while ((fscanf(filePointer, "%s", stringFromFile, MAX_NUMBER_OF_SYMBOLS_IN_STRING)) == 1) {

			stringFromFile = deletePunctuationMark(stringFromFile);
			fprintf(toWriteWithoutPunctuation, "%s\n", stringFromFile);
		}
		free(stringFromFile);
		fprintf(stdout, "Writing without punctuation was succesfully made!\n");
		fclose(toWriteWithoutPunctuation);				//!need to close 	
		fclose(filePointer);
	}
	else {
		if (filePointer == NULL) {
			fprintf(stdout, "File is not created!\n");
			getchar();
			exit(ERROR_OPEN_FILE);
		}
		if (toWriteWithoutPunctuation == NULL) {
			fprintf(stdout, "There were errors in second(copy) file");
			getchar();
			exit(ERROR_OPEN_FILE);
		}
		printf("error opening file");
		getchar();
		exit(ERROR_OPEN_FILE);
	}

	if (toWriteWithoutPunctuation != NULL && toWriteInLowerCase != NULL) {

		char* stringFromFile = (char*)malloc(MAX_NUMBER_OF_SYMBOLS_IN_STRING);
		char* strToLower = (char*)malloc(sizeof(char) * strlen(stringFromFile));
		while (fscanf(readFromFileWithoutPunctuation, "%s", stringFromFile, MAX_NUMBER_OF_SYMBOLS_IN_STRING) == 1)
		{
			fprintf(toWriteInLowerCase, "%s\n", toLowerCase(stringFromFile, strToLower));
		}
		free(strToLower);

		fprintf(stdout, "Writing in lower case was succesfully made\n");
	}



	if (toWriteInLowerCase != NULL && countedWords != NULL)
	{
		rewind(toWriteInLowerCase);
		char* stringFromFile = (char*)malloc(MAX_NUMBER_OF_SYMBOLS_IN_STRING);
		char sep[10] = " ";//////
		int number = 1000000;
		char symbolInFile;
		struct WordCounter* arr;
		arr = (struct WordCounter*)malloc(number * sizeof(struct WordCounter));

		for (int j = 0; j < number; j++)
		{
			arr[j].word = NULL;
			arr[j].count = 0;
		}

		while (fscanf(toWriteInLowerCase, "%s", stringFromFile, MAX_NUMBER_OF_SYMBOLS_IN_STRING) == 1)
		{
			//printf("read: %s\n", stringFromFile);
			for (int i = 0; i < number; i++)
			{
				if (arr[i].word == NULL)
				{
					// step 1: deep copy of given word
					int len = strlen(stringFromFile);
					char* copy = (char*)malloc(len);
					strcpy(copy, stringFromFile);


					//step 2: update value in array
					arr[i].word = copy;
					arr[i].count = 1;

					// step 3: process another word
					//printf("new word is found: %s\n", arr[i].word);
					break;
				}
				else if (strcmp(stringFromFile, arr[i].word) == 0)
				{
					++arr[i].count;
					//printf("counter was updated: %s, %i\n", arr[i].word, arr[i].count);
					break;
				}

			}

		}

		for (int i = 0; i < number; i++)
		{
			if (arr[i].word != NULL)
			{
				fprintf(countedWords, "%s - %d\n", arr[i].word, arr[i].count);
			}
		}
		printf("Words in yoir text were counted!");
		printf("Press any key то Close console window!");
		fclose(countedWords);
		free(stringFromFile);
		free(arr);
	}
	getchar();
}



char* deletePunctuationMark(const char* string)
{
	char* res = (char*)malloc(MAX_NUMBER_OF_SYMBOLS_IN_STRING);
	char* tmp = res;
	do
		if (!ispunct(*string))
			*res++ = *string;
	while (*string++);

	return tmp;
}


char* toLowerCase(char* str, char* strToLower) {

	strcpy(strToLower, str);

	int i = 0;
	while (strToLower[i] != '\0') {
		if (strToLower[i] >= 'A' && strToLower[i] <= 'Z') {
			strToLower[i] -= 'A' - 'a';
		}
		i++;
	}
	return(strToLower);
}
