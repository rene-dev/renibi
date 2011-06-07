#include "alles.h"
bool Ppm::save(char *file){//speichert einen bereich siehe alles.h
	var_pos pos;

	ofstream datei;
	datei.open(file,/* ios_base::binary |*/ ios_base::out);
	datei << "P6" << endl << w << " " << h << endl << "255" << endl;


	pos.y = 0;
	while (pos.y < h){
		pos.x = 0;
		while (pos.x < w){
			datei << getpix(pos, 0);
			datei << getpix(pos, 1);
			datei << getpix(pos, 2);
			pos.x++;
		}
		pos.y++;
	}
// 	datei << pix;
	datei.close();
	return(true);
}

bool Ppm::savesw(char *file){//speichert einen bereich siehe alles.h
	var_pos pos;

	ofstream datei;
	datei.open(file,/* ios_base::binary |*/ ios_base::out);
	datei << "P5" << endl << w << " " << h << endl << "255" << endl;


	pos.y = 0;
	while (pos.y < h){
		pos.x = 0;
		while (pos.x < w){
			datei << gettemp(pos);
			pos.x++;
		}
		pos.y++;
	}
// 	datei << pix;
	datei.close();
	return(true);
}

//#################################################################################################

// bool savesw (var_ppm * ppm, var_pos p1, var_pos p2, char * file){//speichert einen bereich siehe alles.h
// 	var_pos pos;
// 	
// 	p2.x++;
// 	p2.y++;
// 	
// 	ofstream datei;
// 	datei.open(file,/* ios_base::binary |*/ ios_base::out);
// 	datei << "P5" << endl << p2.x - p1.x << " " << p2.y - p1.y<< endl << "255" << endl;
// 	
// 	pos.y = p1.y;
// 	while (pos.y < p2.y){
// 		pos.x = p1.x;
// 		while (pos.x < p2.x){
// 			datei << ppm->pix[pos.x][pos.y][3];
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// 	return(true);
// }
