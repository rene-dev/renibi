#include "alles.h"
int main(int argc, char* argv[]){

	
	var_pos p1, p2, sp1, sp2, start;
	var_pos tux1, tux2;
	var_obj obj;
	var_color colorfarbe, colorab;



	p1.x = 1;
	p1.y = 1;
	p2.x = 640 - 1;
	p2.y = 480 - 1;
	sp1.x = 0;
	sp1.y = 0;
	sp2.x = 640;
	sp2.y = 480;	
	var_keyp key;
	colorfarbe.r = 255;
	colorfarbe.g = 255;
	colorfarbe.b = 255;
	colorab.r = 2;
	colorab.g = 2;
	colorab.b = 2;

// 	var_ppm * org1 = new var_ppm;
// 	var_ppm * org2 = new var_ppm;
	class Ppm bild(640, 480, 3);
// 	class Ppm bild2(640, 480, 3);
	bild.openppm(argv[1]);
// 	bild.filter.colorab = colorab;
	bild.filter.p1 = p1;
	bild.filter.p2 = p2;
// 	bild.fill(1, start);
// 	bild2.filter.p1 = ops.p1;
// 	bild2.filter.p2 = ops.p2;
// 	bild2.insert(bild);
// 	bild.createnext(640, 480, 3);
// 	bild.copy();
// 	bild.next->setmatrix(0);
// 	bild.next->filter.matrixdiv = 0.1;
// 	bild.next->filter.p1 = ops.p1;
// 	bild.next->filter.p2 = ops.p2;
// 	bild.next->faltungpix();
// 	bild.diffpix();
// 		var_obj obj;
		//obj =	bild.openobj(argv[2]);
// while(true){
// 		cout << "mitte.x:" << endl << flush;
// 		cin >> sp1.x;
// 		cout << "mitte.y:" << endl << flush;
// 		cin >> sp1.y;
// 
// 		cout << "x:" << endl << flush;
// 		cin >> sp2.x;
// 		cout << "y:" << endl << flush;
// 		cin >> sp2.y;
// 
// 		key = bild.sift(sp1, sp2.x, sp2.y);
// 		cout 	<< "0: " << (int)key.key[0] << endl
// 				<< "1: " << (int)key.key[1] << endl
// 				<< "2: " << (int)key.key[2] << endl
// 				<< "3: " << (int)key.key[3] << endl
// 				<< "4: " << (int)key.key[4] << endl
// 				<< "5: " << (int)key.key[5] << endl
// 				<< "6: " << (int)key.key[6] << endl
// 				<< "7: " << (int)key.key[7] << endl
// 				<< "ori: " << (int)key.ori << endl
// 				<< "scale: " << (float)key.scale << endl << flush;
// }
//		cout << "Algemeine Tux-Unwahrscheinlichkeit: " << endl << flush << bild.matchobj(obj) << endl << flush;
 	bild.setmatrix(3);
 	bild.faltungpix();
	
// 	bild.filter.tresh = 3;
// 	bild.rgb2hsvpix();
/*
tux1.x = 232;
tux1.y = 4;
tux2.x = 628;
tux2.y = 473;

obj.image = bild.openimage(argv[2]);
cout << "tux: " << bild.scalendiff(tux1, tux2, obj);

*/

 	bild.save(argv[2]);
// 	bild.hsv2rgbpix();
// 	bild.skeletpix();
// cout << "hallo" << endl << flush;

// 	bild.save(argv[3]);
// 	bild.next->saveppm(argv[3]);
// 	return(1);

}

