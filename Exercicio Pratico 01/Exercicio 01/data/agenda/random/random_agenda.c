/**
 * This code is under GNU License Version 3.
 * 
 * Create by Wesklei Migliorini
 */

// Including some library

#include "../../../main.h"

#ifndef const_chars
#define const_chars

/** Here I will create an array of prefixes to help generate names.
* I am banking on multiplication to ensure a large number of names
* by using 7 prefixes and 20 stems, and 16 suffixes I should be able to
* create about 7 * 20 * 16 = 2240 names out of 312 bytes of data (In my earlier
* example from the forum I used this code to generate male and female names,
* but here I combined them).
*/
const char NamesPrefix[][5] = {
	"", //who said we need to add a prefix?
	"bel", //lets say that means "the good"
	"nar", //"The not so good as Bel"
	"xan", //"The evil"
	"bell", //"the good"
	"natr", //"the neutral/natral"
	"ev", //Man am I original
};

const char NamesSuffix[][5] = {
	"", "us", "ix", "ox", "ith",
	"ath", "um", "ator", "or", "axia",
	"imus", "ais", "itur", "orex", "o",
	"y"
};


const char NamesStems[][10] = {
	"adur", "aes", "anim", "apoll", "imac",
	"educ", "equis", "extr", "guius", "hann",
	"equi", "amora", "hum", "iace", "ille",
	"inept", "iuv", "obe", "ocul", "orbis"
};


const char PlacePrefix[][10] = {
	"city ", //lets say that means "the good"
	"country ", //"The not so good as Bel"
	"stade ", //"The evil"
	"gymnasium ", //"the good"
	"gym ", //"the neutral/natral"
	"Block ", //Man am I original
};

const char PlaceSuffix[][5] = {
	"", "us", "ix", "ox", "ith",
	"ath", "um", "ator", "or", "axia",
	"imus", "ais", "itur", "orex", "o",
	"y"
};


const char PlaceStems[][10] = {
	"adur", "aes", "anim", "apoll", "imac",
	"educ", "equis", "extr", "guius", "hann",
	"equi", "amora", "hum", "iace", "ille",
	"inept", "iuv", "obe", "ocul", "orbis"
};
#endif



/**
 * Generate random time name
 */
void randomNome(char* nome)
{
	nome[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(nome, NamesPrefix[(rand() % 7)]);
	//add the stem...
	strcat(nome, NamesStems[(rand() % 20)]);
	//add the suffix...
	strcat(nome, NamesSuffix[(rand() % 16)]);
	//Make the first letter capital...
	nome[0]=toupper(nome[0]);
	
}

/**
 * Generate random adress
 */
void randomEndereco(char* endereco)
{
	endereco[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(endereco, PlacePrefix[(rand() % 6)]);
	//add the stem...
	char stems[6];
        strcpy(stems,PlaceStems[(rand() % 20)]);
	stems[0] = toupper(stems[0]);
	strcat(endereco, stems);
	//add the suffix...
	strcat(endereco, PlaceSuffix[(rand() % 16)]);
	//Make the first letter capital...
	endereco[0]=toupper(endereco[0]);
}

void randomFone(char* fone, int dim)
{
	int i;
	for(i=0;i<dim;i++)
	{	
		sprintf(&fone[i],"%d",rand() % 9);
	}
}
/**
 * Generate random AGENDA using others random metods
 */
void randomAgenda(ppAGENDA ppAgenda, int cod)
{
	(*ppAgenda)->cod=cod;
	randomNome((*ppAgenda)->nome);
	randomEndereco((*ppAgenda)->end);
	randomFone((*ppAgenda)->fone,10);
}
