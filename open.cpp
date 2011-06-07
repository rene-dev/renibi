#include "alles.h"

bool Ppm::openppm(char * file){//siehe alles.h
	char * buffer = new char[h * w * t];
	char res[5];
	int i = 0;
	ifstream datei;
	datei.open(file,/* ios_base::binary | */ios_base::in);
	if(datei.good()){
		cout << file << "\terfolgreich (-:\n" << flush;
	}
	else{
		cout << file << "\terror beim öffnen )-:\n" << flush;
		abort();
	}
				
	datei.seekg(0, ios::beg);
	//##########	magic nummer	##########
	if(datei.get() != 'P' || datei.get() != '6'){
		abort();
	}

	datei.get();

	//##########	komentar	##########
	while(datei.get() == '#'){
		while(datei.get() != '\n'){}
	}
	datei.unget();

	//##########	x	##########
	res[i] = datei.get();
	i++;

	while(res[i-1] != ' '){
		res[i] = datei.get();
		i++;
	}

	res[i] = '\0';
	i = 0;

//##########	y	##########
	res[i] = datei.get();
	i++;
	while(res[i-1] != '\n'){
		res[i] = datei.get();
		i++;
	}

	res[i] = '\0';

//##########	komentar	##########
	while(datei.get() == '#'){
		while(datei.get() != '\n'){}
	}
	datei.unget();

//##########	d	##########
	res[i] = datei.get();
	i++;

	while(res[i-1] != '\n'){
		res[i] = datei.get();
		i++;
	}

	res[i] = '\0';
	datei.unget();

	if(datei.get() == '\n'){
		cout << "passte!!(=" << endl << flush;
	}

//##########	Bild	##########
	datei.read(buffer, h * w * 3);
	datei.close();
	delete []pix;
	pix = (unsigned char *)buffer;
	return(true);
}

unsigned char * Ppm::openimage(char * file){
	char * buffer = new char[100 * 100 * 3];

	ifstream datei;
	datei.open(file,/* ios_base::binary | */ios_base::in);
	if(datei.good()){
		cout << file << "\terfolgreich geöffnetes vergleichs ding (-:\n" << flush;
	}
	else{
		cout << file << "\terror beim öffnen des vergleichs dings )-:\n" << flush;
		return(false);
		abort();
	}
				
	datei.seekg(0, ios::beg);
	datei.read(buffer, 100 * 100 * 3);
	datei.close();

	return ((unsigned char *)buffer);
}

var_obj Ppm::openobj(char * file){
	char * buffer = new char[100 * 102 * 3];
	var_obj obj;
// 	char name[21];
	struct var_keyp *nextkey;
	
	nextkey = &obj.key;

	ifstream datei;
	datei.open(file,/* ios_base::binary | */ios_base::in);
	if(datei.good()){
		cout << file << "\terfolgreich geöffnetes obj (-:\n" << flush;
	}
	else{
		cout << file << "\terror beim öffnen des vergleich obj )-:\n" << flush;
		abort();
	}
				
	datei.seekg(0, ios::beg);
	datei.getline(obj.name, 21);
	datei.get();
	datei.read(buffer, 100 * 100 * 3);
	obj.image = new unsigned char[100 * 102 *3];
	for(int i = 0; i < 100 * 100 * 3; i++){obj.image[i] = (unsigned char) buffer[i];}

	datei.get();
	while(true){
		nextkey->color.r = datei.get();
		nextkey->color.g = datei.get();
		nextkey->color.b = datei.get();
		nextkey->key[0] = datei.get();
		nextkey->key[1] = datei.get();
		nextkey->key[2] = datei.get();
		nextkey->key[3] = datei.get();
		nextkey->key[4] = datei.get();
		nextkey->key[5] = datei.get();
		nextkey->key[6] = datei.get();
		nextkey->key[7] = datei.get();
		nextkey->ori = datei.get();
		nextkey->x = 0;
		nextkey->y = 0;
		nextkey->scale = 0;
		nextkey->next = NULL;
		datei.unget();
		if(datei.eof()){
			break;
		}

		datei.get();
		nextkey->next = new var_keyp;
		nextkey = nextkey->next;
	}
	datei.close();
	return (obj);
}

// true ? war : falsch


