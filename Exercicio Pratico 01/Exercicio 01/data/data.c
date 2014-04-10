/**
 * This code is under GNU License Version 3.
 * 
 * Create by Wesklei Migliorini
 */

// Calling some librarys
#include "../main.h"

#define APPENDB 	"a+b"
#define READB		"r"

void openFile(FILE **ppFile, char* param)
{
	(*ppFile) = fopen(FULLFILEPATH,param);
	if((*ppFile) == NULL)
	{
		fileGenericProblemError();
	}
}

void closeFile(FILE **ppFile)
{
	fclose((*ppFile));
}

long currentSizeInFile(FILE** ppFile)
{
	long retValue = -1;
		retValue = ftell(*ppFile);
	return retValue;
}

/**
 * Set in second parameter a string representative of DataType
 */
void getStringOfType(DataType type, char *typeofData){
	switch(type){

		case TYPE_PARTIDA:
			strcpy(typeofData,"PARTIDA");
			break;

		default:
			strcpy(typeofData,"NULL");
	}
}

void printEntries(pDATA pData)
{
	//printf("ID: %d\n",pData->id);
	DATA data;
        memcpy(&data,pData,sizeof(DATA));	

	printf("Cod: %d\n",data.agenda.cod);
	printf("Nome: %s\n",data.agenda.nome);
	printf("Endereco: %s\n",data.agenda.end);
	printf("fone: %s\n",data.agenda.fone);
}
