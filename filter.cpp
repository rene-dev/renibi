#include "alles.h"
//#################################################################################################
bool Ppm::diffpix(void){
	var_pos pos;
	unsigned char k = 0;
// 	cout << "1.hallo" << endl << flush;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			k = 0;
			while(k < 3){
				setpix(pos, k, (
					(getpix(pos, k) < next->getpix(pos, k))
					?
					(next->getpix(pos, k) - getpix(pos, k))
					:
					(getpix(pos, k) - next->getpix(pos, k))));
// 					cout << "2.hallo" << endl << flush;
				k++;
			}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::diffpix2(void){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			setpix(pos, 0, (
				(getpix(pos, 0) < filter.color.r)
				?
				(filter.color.r - getpix(pos, 0))
				:
				(getpix(pos, 0) - filter.color.r)));

			setpix(pos, 1, (
				(getpix(pos, 1) < filter.color.g)
				?
				(filter.color.g - getpix(pos, 1))
				:
				(getpix(pos, 1) - filter.color.g)));

			setpix(pos, 2, (
				(getpix(pos, 2) < filter.color.b)
				?
				(filter.color.b - getpix(pos, 2))
				:
				(getpix(pos, 2) - filter.color.b)));
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::difftemp(void){
	var_pos pos;
// 	cout << "1.hallo" << endl << flush;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			settemp(pos, (
				(gettemp(pos) < next->gettemp(pos))
				?
				(next->gettemp(pos) - gettemp(pos))
				:
				(gettemp(pos) - next->gettemp(pos))));
// 				cout << "2.hallo" << endl << flush;
			
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::difftemp2(unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			settemp(pos, (
				(gettemp(pos) < val)
				?
				(val - gettemp(pos))
				:
				(gettemp(pos) - val)));
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
//#################################################################################################
bool Ppm::faltungpix(void){
	unsigned char *tempbild = new unsigned char [(short int)(filter.p2.x - filter.p1.x) * (filter.p2.y - filter.p1.y) * t];
	var_pos pos;
	unsigned char k;
	float temp;
	pos.y = filter.p1.y;
	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			k = 0;
			while(k < t){
				temp = (float)(
						filter.matrix[0][0] * getpix(pos.x - 1,	pos.y - 1,	k)
					+	filter.matrix[1][0] * getpix(pos.x,	pos.y - 1,	k)
					+	filter.matrix[2][0] * getpix(pos.x + 1,	pos.y - 1,	k)
					+ 	filter.matrix[0][1] * getpix(pos.x - 1,	pos.y,		k)
					+	filter.matrix[1][1] * getpix(pos.x,	pos.y,		k)
					+ 	filter.matrix[2][1] * getpix(pos.x + 1,	pos.y,		k)
					+ 	filter.matrix[0][2] * getpix(pos.x - 1,	pos.y + 1,	k)
					+ 	filter.matrix[1][2] * getpix(pos.x,	pos.y + 1,	k)
					+ 	filter.matrix[2][2] * getpix(pos.x + 1,	pos.y + 1,	k)
						)
					/	filter.matrixdiv;
									
				tempbild[((pos.y - filter.p1.y) * (filter.p2.x - filter.p1.x) + (pos.x - filter.p1.x)) * t + k] = static_cast <unsigned char> ((temp < 0) ? -temp : temp);
				k++;
			}
			pos.x++;
		}
		pos.y++;
	}
// 	delete []pix;
// 	pix = tempbild;
	pos.y = filter.p1.y;
	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			k = 0;
			while(k < t){
				setpix(pos, k, tempbild[((pos.y - filter.p1.y) * (filter.p2.x - filter.p1.x) + (pos.x - filter.p1.x)) * t + k]);
				k++;
			}
			pos.x++;
		}
		pos.y++;
	}
	delete []tempbild;
	return(true);
}
bool Ppm::faltungtemp(void){
	unsigned char *tempbild = new unsigned char [(short int)(filter.p2.x - filter.p1.x) * (filter.p2.y - filter.p1.y)];
	var_pos pos;
	int temp;
	pos.y = filter.p1.y;
	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){

			temp = static_cast <int> ((
					filter.matrix[0][0] * gettemp(pos.x - 1, pos.y - 1)
				+	filter.matrix[1][0] * gettemp(pos.x    , pos.y - 1)
				+	filter.matrix[2][0] * gettemp(pos.x + 1, pos.y - 1)
				+ 	filter.matrix[0][1] * gettemp(pos.x - 1, pos.y    )
				+	filter.matrix[1][1] * gettemp(pos.x    , pos.y    )
				+ 	filter.matrix[2][1] * gettemp(pos.x + 1, pos.y    )
				+ 	filter.matrix[0][2] * gettemp(pos.x - 1, pos.y + 1)
				+ 	filter.matrix[1][2] * gettemp(pos.x    , pos.y + 1)
				+ 	filter.matrix[2][2] * gettemp(pos.x + 1, pos.y + 1)
					)
				/	filter.matrixdiv);
								
				tempbild[(pos.y - filter.p1.y) * (filter.p2.x - filter.p1.x) + (pos.x - filter.p1.x)] = ((unsigned char)(temp < 0) ? -temp : temp);
			pos.x++;
		}
		pos.y++;
	}
// 	delete []temp;
// 	temp = tempbild;
	pos.y = filter.p1.y;
	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			settemp(pos, tempbild[(pos.y - filter.p1.y) * (filter.p2.x - filter.p1.x) + (pos.x - filter.p1.x)]);
			pos.x++;
		}
		pos.y++;
	}
	delete []tempbild;

	return(true);
}
//#################################################################################################
bool Ppm::setmatrix(unsigned char i){
	switch(i){
		case 0://gauss 1
			filter.matrix[0][0] = 0;		filter.matrix[1][0] = 1;		filter.matrix[2][0] = 0;
			filter.matrix[0][1] = 1;		filter.matrix[1][1] = 4;		filter.matrix[2][1] = 1;
			filter.matrix[0][2] = 0;		filter.matrix[1][2] = 1;		filter.matrix[2][2] = 0;
			filter.matrixdiv = 8;
		break;

		case 1://gauss 2
			filter.matrix[0][0] = 1;		filter.matrix[1][0] = 2;		filter.matrix[2][0] = 1;
			filter.matrix[0][1] = 2;		filter.matrix[1][1] = 8;		filter.matrix[2][1] = 2;
			filter.matrix[0][2] = 1;		filter.matrix[1][2] = 2;		filter.matrix[2][2] = 1;
			filter.matrixdiv = 20;
		break;

		case 2://laplace 1
			filter.matrix[0][0] = 0;		filter.matrix[1][0] = -1;		filter.matrix[2][0] = 0;
			filter.matrix[0][1] = -1;		filter.matrix[1][1] = 4;		filter.matrix[2][1] = -1;
			filter.matrix[0][2] = 0;		filter.matrix[1][2] = -1;		filter.matrix[2][2] = 0;
			filter.matrixdiv = 1;
		break;

		case 3://laplace 2
			filter.matrix[0][0] = -1;		filter.matrix[1][0] = -2;		filter.matrix[2][0] = -1;
			filter.matrix[0][1] = -2;		filter.matrix[1][1] = 8;		filter.matrix[2][1] = -2;
			filter.matrix[0][2] = -1;		filter.matrix[1][2] = -2;		filter.matrix[2][2] = -1;
			filter.matrixdiv = 4;
		break;

		case 4:
			filter.matrix[0][0] = 0;		filter.matrix[1][0] = 0;		filter.matrix[2][0] = 0;
			filter.matrix[0][1] = 0;		filter.matrix[1][1] = 0;		filter.matrix[2][1] = 0;
			filter.matrix[0][2] = 0;		filter.matrix[1][2] = 0;		filter.matrix[2][2] = 0;
			filter.matrixdiv = 1;
		break;

		case 5:
			filter.matrix[0][0] = 0;		filter.matrix[1][0] = 0;		filter.matrix[2][0] = 0;
			filter.matrix[0][1] = 0;		filter.matrix[1][1] = 1;		filter.matrix[2][1] = 0;
			filter.matrix[0][2] = 0;		filter.matrix[1][2] = 0;		filter.matrix[2][2] = 0;
			filter.matrixdiv = 1;
		break;

		default:
			cout << "Fehler in der Matrix" << endl << flush;
		break;
	}
	return(true);
}
//#################################################################################################
bool Ppm::makesw(void){
	var_pos pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			settemp(pos, (unsigned char)(getpix(pos, 0) + getpix(pos, 1) + getpix(pos, 2)) / 3);
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::makesw(unsigned char d){
	var_pos pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			settemp(pos, getpix(pos, d));
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
//#################################################################################################
var_keyp Ppm::sift(var_pos pos, unsigned char tx, unsigned char ty){
	struct vartemp_keyp{
		unsigned char x, y, ori; //Hauptrichtung
/*		float skale;*/
		int key[8];//histogramm
	} temp;


	var_pos p1, p2, tpos;
	var_keyp out;
	float x, y, siftmin = 5 * 5, d = 0;
	unsigned char i = 0;
	out.scale = out.x = out.y = out.ori = 0;
	if(pos.x - tx >= 0 && pos.y - ty >= 0 && pos.x + tx <= w && pos.y + ty <= h){
	p1.x = pos.x - tx;
	p1.y = pos.y - ty;
	p2.x = pos.x + tx;
	p2.y = pos.y + ty;
	temp.x = tx;
	temp.y = ty;
	tpos = p1;
	}
	else{
		return(out);
	}
	makesw();
	for(int k = 0; k < 8; k++){temp.key[k] = 0;}

	while(tpos.y < p2.y){
		tpos.x = p1.x;
		while(tpos.x < p2.x){
			if(getpix(tpos, 0) != 255 && getpix(tpos, 1) != 255 && getpix(tpos, 2) != 255){
				y =
					 -1 * getsw(tpos.x - 1, tpos.y - 1)
				+	 -2 * getsw(tpos.x    , tpos.y - 1)
				+	 -1 * getsw(tpos.x + 1, tpos.y - 1)
				+ 	 0  * getsw(tpos.x - 1, tpos.y    )
				+	 0  * getsw(tpos.x    , tpos.y    )
				+ 	 0  * getsw(tpos.x + 1, tpos.y    )
				+ 	 1  * getsw(tpos.x - 1, tpos.y + 1)
				+ 	 2  * getsw(tpos.x    , tpos.y + 1)
				+ 	 1  * getsw(tpos.x + 1, tpos.y + 1);
				x =
					 -1 * getsw(tpos.x - 1, tpos.y - 1)
				+	 0  * getsw(tpos.x    , tpos.y - 1)
				+	 1  * getsw(tpos.x + 1, tpos.y - 1)
				+ 	 -2 * getsw(tpos.x - 1, tpos.y    )
				+	 0  * getsw(tpos.x    , tpos.y    )
				+ 	 2  * getsw(tpos.x + 1, tpos.y    )
				+ 	 -1 * getsw(tpos.x - 1, tpos.y + 1)
				+ 	 0  * getsw(tpos.x    , tpos.y + 1)
				+ 	 1  * getsw(tpos.x + 1, tpos.y + 1);
			
			
				if(-0.5 * x < y && y <  0.5 * x && x * x + y * y > siftmin){if(x > 0){temp.key[0]++;}else{temp.key[4]++;}}
				if( 0.5 * x < y && y <  2.0 * x && x * x + y * y > siftmin){if(x > 0){temp.key[1]++;}else{temp.key[5]++;}}
				if( 2.0 * x < y && y < -2.0 * x && x * x + y * y > siftmin){if(y > 0){temp.key[2]++;}else{temp.key[6]++;}}
				if(-2.0 * x < y && y < -0.5 * x && x * x + y * y > siftmin){if(y > 0){temp.key[3]++;}else{temp.key[7]++;}} 
			}
			tpos.x++;
		}
		tpos.y++;
	}
	for(int k = 0; k < 8; k++){if(temp.key[k] > d){d = temp.key[k]; i = k;}}
	cout << "in fill d: " << d << endl << flush;
	x = 254 / d;
	cout << "in fill x: " << x << endl << flush;

	out.scale = x;
	out.x = temp.x;
	out.y = temp.y;
	out.next = NULL;
	switch(i){
		case 0:
			out.key[0] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[7] * x);
			out.ori = 0;
		break;
		case 1:
			out.key[0] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[0] * x);
			out.ori = 1;
		break;
		case 2:
			out.key[0] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[1] * x);
			out.ori = 2;
		break;
		case 3:
			out.key[0] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[2] * x);
			out.ori = 3;
		break;
		case 4:
			out.key[0] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[3] * x);
			out.ori = 4;
		break;
		case 5:
			out.key[0] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[4] * x);
			out.ori = 5;
		break;
		case 6:
			out.key[0] = static_cast <unsigned char> (temp.key[6] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[5] * x);
			out.ori = 6;
		break;
		case 7:
			out.key[0] = static_cast <unsigned char> (temp.key[7] * x);
			out.key[1] = static_cast <unsigned char> (temp.key[0] * x);
			out.key[2] = static_cast <unsigned char> (temp.key[1] * x);
			out.key[3] = static_cast <unsigned char> (temp.key[2] * x);
			out.key[4] = static_cast <unsigned char> (temp.key[3] * x);
			out.key[5] = static_cast <unsigned char> (temp.key[4] * x);
			out.key[6] = static_cast <unsigned char> (temp.key[5] * x);
			out.key[7] = static_cast <unsigned char> (temp.key[6] * x);
			out.ori = 7;
		break;

	}
	return(out);
}
unsigned short int Ppm::matchkey(var_keyp in1,var_keyp in2 ){
	unsigned short int out = 0;
	for(int i = 0; i < 8; i++){out +=(in1.key[i] - in2.key[i]) * (in1.key[i] - in2.key[i]);}
	return(out);
}
unsigned int Ppm::matchobj(var_obj obj){
	struct var_keyp *nextkey;
	struct var_pos p1, p2;
	nextkey = &obj.key;
	p1 = filter.p2;
	p2 = filter.p1;

	while(nextkey){

		match1objkey(*nextkey);
		if(tempvars.p1.x < p1.x){p1.x = tempvars.p1.x;}
		if(tempvars.p1.y < p1.y){p1.y = tempvars.p1.y;}
		if(tempvars.p2.x > p2.x){p2.x = tempvars.p2.x;}
		if(tempvars.p2.y > p2.y){p2.y = tempvars.p2.y;}
		nextkey = nextkey->next;
	}
	return(scalendiff(p1, p2, obj));
}
bool Ppm::match1objkey(var_keyp key){

	struct diff{
		unsigned short int keydiff;
		struct var_pos p1, p2, pos;
		struct diff *nextdiff;
	} diff, *nextdiff;
			cout << "bla1" << endl << flush;

	unsigned short int xyz = 0, i = 999999999;
	var_pos pos = filter.p1;
	filter.color = key.color;
	filter.colorab.r = 50;
	filter.colorab.g = 50;
	filter.colorab.b = 50;
	nextdiff = &diff;
			cout << "bla2" << endl << flush;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
// 			cout << "bla2.5" << endl << flush;

			if(erkannt(pos)){
			cout << "bla3" << endl << flush;

				fillmo(pos, 0);
			cout << "bla4" << endl << flush;

				if(tempvars.count){
					tempvars.pos.x = (short int) tempvars.x / tempvars.count;
					tempvars.pos.y = (short int) tempvars.y / tempvars.count;
				}
				else{
					tempvars.pos = filter.p1;
				}
			cout << "bla5" << endl << flush;

				tempvars.key = sift(tempvars.pos, static_cast <unsigned char> (tempvars.p2.x - tempvars.p1.x) * 0.75, static_cast <unsigned char> (tempvars.p2.y - tempvars.p1.y) * 0.75);
				nextdiff->p1 = tempvars.p1;
				nextdiff->p2 = tempvars.p2;
				nextdiff->pos = tempvars.pos;
			cout << "bla5" << endl << flush;

				nextdiff->keydiff = matchkey(tempvars.key, key);
			cout << "bla6" << endl << flush;

				nextdiff->nextdiff = new struct diff;
				nextdiff = nextdiff->nextdiff;
				nextdiff->nextdiff = NULL;
				xyz = 1;
			cout << "bla7" << endl << flush;

			}
			pos.x++;
		}
		pos.y++;
	}
	if(!xyz){
		return(false);
	}
			cout << "bla8" << endl << flush;

	nextdiff = &diff;
	while(nextdiff){
		if(i > nextdiff->keydiff){
			i = nextdiff->keydiff;
			tempvars.p1 = nextdiff->p1;
			tempvars.p2 = nextdiff->p2;
			tempvars.pos = nextdiff->pos;
			cout << "bla" << endl << flush;
		}
		nextdiff = nextdiff->nextdiff;
	}
	tempvars.count = i;
	return(true);
}
//################################################################################################
bool Ppm::treshpix(void){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, 0) < filter.treshcolor.r){setpix(pos, 0, filter.color.r);}
			if(getpix(pos, 1) < filter.treshcolor.g){setpix(pos, 1, filter.color.g);}
			if(getpix(pos, 2) < filter.treshcolor.b){setpix(pos, 2, filter.color.b);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix(unsigned char d, unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, d) < filter.tresh){setpix(pos, d, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshtemp(unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(gettemp(pos) < filter.tresh){settemp(pos, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix2(void){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, 0) > filter.treshcolor.r){setpix(pos, 0, filter.color.r);}
			if(getpix(pos, 1) > filter.treshcolor.g){setpix(pos, 1, filter.color.g);}
			if(getpix(pos, 2) > filter.treshcolor.b){setpix(pos, 2, filter.color.b);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix2(unsigned char d, unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, d) > filter.tresh){setpix(pos, d, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshtemp2(unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(gettemp(pos) > filter.tresh){settemp(pos, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix3(void){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, 0) > filter.treshcolor.r && getpix(pos, 0) < filter.treshcolor2.r){setpix(pos, 0, filter.color.r);}
			if(getpix(pos, 1) > filter.treshcolor.g && getpix(pos, 1) < filter.treshcolor2.g){setpix(pos, 1, filter.color.g);}
			if(getpix(pos, 2) > filter.treshcolor.b && getpix(pos, 2) < filter.treshcolor2.b){setpix(pos, 2, filter.color.b);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix3(unsigned char d, unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, d) > filter.tresh && getpix(pos, d) < filter.tresh2){setpix(pos, d, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshtemp3(unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(gettemp(pos) > filter.tresh && gettemp(pos) < filter.tresh2){settemp(pos, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix4(void){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, 0) < filter.treshcolor.r && getpix(pos, 0) > filter.treshcolor2.r){setpix(pos, 0, filter.color.r);}
			if(getpix(pos, 1) < filter.treshcolor.g && getpix(pos, 1) > filter.treshcolor2.g){setpix(pos, 1, filter.color.g);}
			if(getpix(pos, 2) < filter.treshcolor.b && getpix(pos, 2) > filter.treshcolor2.b){setpix(pos, 2, filter.color.b);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshpix4(unsigned char d, unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(getpix(pos, d) < filter.tresh && getpix(pos, d) > filter.tresh2){setpix(pos, d, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::treshtemp4(unsigned char val){
	var_pos pos;
	pos = filter.p1;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(gettemp(pos) < filter.tresh && gettemp(pos) > filter.tresh2){settemp(pos, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
//#################################################################################################
bool Ppm::skeletpix(void){
	var_pos pos;
	pos = filter.p1;
	unsigned char k, temp, wert;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			k = 0;
				
			while(k < 3){
				temp = 0;
				wert = getpix(pos, k);
				if(wert <= getpix(pos.x - 1, pos.y - 1, k)){temp ++;}
				if(wert <= getpix(pos.x    , pos.y - 1, k)){temp ++;}
				if(wert <= getpix(pos.x + 1, pos.y - 1, k)){temp ++;}
				if(wert <= getpix(pos.x - 1, pos.y    , k)){temp ++;}
				if(wert <= getpix(pos.x    , pos.y    , k)){temp ++;}
				if(wert <= getpix(pos.x + 1, pos.y    , k)){temp ++;}
				if(wert <= getpix(pos.x - 1, pos.y + 1, k)){temp ++;}
				if(wert <= getpix(pos.x    , pos.y + 1, k)){temp ++;}
				if(wert <= getpix(pos.x + 1, pos.y + 1, k)){temp ++;}
				if(temp > filter.tresh){setpix(pos, k,  (k == 0) ?  ((k == 1) ? filter.color.b : filter.color.g) : filter.color.r);}				
				k++;
			}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
bool Ppm::skelettemp(unsigned char val){
	var_pos pos;
	pos = filter.p1;
	unsigned char temp, wert;

	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			temp = 0;
			wert = gettemp(pos);
			if(wert <= gettemp(pos.x - 1, pos.y - 1)){temp ++;}
			if(wert <= gettemp(pos.x    , pos.y - 1)){temp ++;}
			if(wert <= gettemp(pos.x + 1, pos.y - 1)){temp ++;}
			if(wert <= gettemp(pos.x - 1, pos.y    )){temp ++;}
			if(wert <= gettemp(pos.x    , pos.y    )){temp ++;}
			if(wert <= gettemp(pos.x + 1, pos.y    )){temp ++;}
			if(wert <= gettemp(pos.x - 1, pos.y + 1)){temp ++;}
			if(wert <= gettemp(pos.x    , pos.y + 1)){temp ++;}
			if(wert <= gettemp(pos.x + 1, pos.y + 1)){temp ++;}
			if(temp > filter.tresh){settemp(pos,  val);}				
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
//#################################################################################################
bool Ppm::fill(unsigned char count, var_pos start){
	return(fill(count, start, getpix(start), 0));
}
bool Ppm::fill(short int count, var_pos start, var_color vorher , unsigned char head/*, int &tempx, int &tempy, int &tempcount*/){
// 	cout << start.x << " " << start.y << endl << flush;
 	if(!head){tempvars.x = tempvars.y = tempvars.count = 0; filter.tp1 = filter.tp2 = start;}
// 	unsigned int tempcount;
	if(start.x <= filter.p1.x){return(true);}
	if(start.x >= filter.p2.x){return(true);}
	if(start.y <= filter.p1.y){return(true);}
	if(start.y >= filter.p2.y){return(true);}

	if(erkannt(start, vorher) && gettemp(start) == 0){

		tempvars.x += start.x;
		tempvars.y += start.y;
		tempvars.count++;
		settemp(start, (unsigned char)count);//kontrast
// 		setpix(start, 255, 0, 0);
		if(start.x < tempvars.p1.x){tempvars.p1.x = start.x;}
		if(start.y < tempvars.p1.y){tempvars.p1.y = start.y;}
		if(start.x > tempvars.p2.x){tempvars.p2.x = start.x;}
		if(start.y > tempvars.p2.y){tempvars.p2.y = start.y;}

		vorher = getpix(start);
		setpix(start, 255, 0, 0);
		if(head != 2){
			start.x++;
			fill(count, start, vorher, 4/*, tempx, tempy, tempcount*/);
			start.x--;
		}
				
		if(head != 1){
			start.y++;
			fill(count, start, vorher, 3/*, tempx, tempy, tempcount*/);
			start.y--;
		}
				
		if(head != 4){
			start.x--;
			fill(count, start, vorher, 2/*, tempx, tempy, tempcount*/);
			start.x++;
		}
				
		if(head != 3){
			start.y--;
			fill(count, start, vorher, 1/*, tempx, tempy, tempcount*/);
			start.y++;
		}
		
	}
    
	return(true);
 
}
var_pos Ppm::fill2(unsigned char count, var_pos start){
	var_pos pos;
	
	fill2(count, start, getpix(start), 0);
	pos.x = (short int)tempvars.x / tempvars.count;
	pos.y = (short int)tempvars.y / tempvars.count;
	return(pos);
}
bool Ppm::fill2(short int count, var_pos start, var_color vorher , unsigned char head/*, int &tempx, int &tempy, int &tempcount*/){
// 	cout << start.x << " " << start.y << endl << flush;
 	if(!head){tempvars.x = tempvars.y = tempvars.count = 0; filter.tp1 = filter.tp2 = start;}
// 	unsigned int tempcount;
	if(start.x <= filter.p1.x){return(true);}
	if(start.x >= filter.p2.x){return(true);}
	if(start.y <= filter.p1.y){return(true);}
	if(start.y >= filter.p2.y){return(true);}
	if(erkannt(start, vorher) && gettemp(start) == 0){

		tempvars.x += start.x;
		tempvars.y += start.y;
		tempvars.count++;
		settemp(start, (unsigned char)count);//kontrast
// 		setpix(start, 255, 0, 0);
		if(start.x < filter.tp1.x){filter.tp1.x = start.x;}
		if(start.y < filter.tp1.y){filter.tp1.y = start.y;}
		if(start.x > filter.tp2.x){filter.tp2.x = start.x;}
		if(start.y > filter.tp2.y){filter.tp2.y = start.y;}
// 		vorher = getpix(start);
		setpix(start, 255, 0, 0);
		if(head != 2){
			start.x++;
			fill(count, start, vorher, 4/*, tempx, tempy, tempcount*/);
			start.x--;
		}
				
		if(head != 1){
			start.y++;
			fill(count, start, vorher, 3/*, tempx, tempy, tempcount*/);
			start.y--;
		}
				
		if(head != 4){
			start.x--;
			fill(count, start, vorher, 2/*, tempx, tempy, tempcount*/);
			start.x++;
		}
				
		if(head != 3){
			start.y--;
			fill(count, start, vorher, 1/*, tempx, tempy, tempcount*/);
			start.y++;
		}
		
	}
    
	return(true);
 
}
//#################################################################################################
bool Ppm::settemp(unsigned char val){
	var_pos pos;
	pos = filter.p1;
	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			settemp(pos, val);
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
//#################################################################################################
bool Ppm::searchpix(unsigned char val){
	var_pos pos = filter.p1;
	while(pos.y < filter.p2.y){
		pos.x = filter.p1.x;
		while(pos.x < filter.p2.x){
			if(erkannt(pos, filter.color)){settemp(pos, val);}
			pos.x++;
		}
		pos.y++;
	}
	return(true);
}
//#################################################################################################
bool Ppm::fillmo(var_pos start, unsigned char head = 0){
	if(!head){tempvars.x = tempvars.y = tempvars.count = 0; tempvars.p1 = tempvars.p2 = start;cout << "bla" << flush;}
	if(start.x <= filter.p1.x){return(true);}
	if(start.x >= filter.p2.x){return(true);}
	if(start.y <= filter.p1.y){return(true);}
	if(start.y >= filter.p2.y){return(true);}
	if(erkannt(start) && gettemp(start) == 0){
		tempvars.x += start.x;
		tempvars.y += start.y;
		tempvars.count++;
		settemp(start, 1);//kontrast
// 		setpix(start, 255, 0, 0);
		if(start.x < tempvars.p1.x){tempvars.p1.x = start.x;}
		if(start.y < tempvars.p1.y){tempvars.p1.y = start.y;}
		if(start.x > tempvars.p2.x){tempvars.p2.x = start.x;}
		if(start.y > tempvars.p2.y){tempvars.p2.y = start.y;}
		
		if(head != 2){
			start.x++;
			fillmo(start, 4);
			start.x--;
		}
				
		if(head != 1){
			start.y++;
			fillmo(start, 3);
			start.y--;
		}
				
		if(head != 4){
			start.x--;
			fillmo(start, 2);
			start.x++;
		}
				
		if(head != 3){
			start.y--;
			fillmo(start, 1);
			start.y++;
		}
	}
	return(true);
}
//#################################################################################################
void Ppm::line(short int x1, short int y1, short int x2, short int y2){
	var_color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	int dy = y2 - y1;
	int dx = x2 - x1;
	int stepx, stepy;
	
	if(dy < 0){
		dy = -dy;  stepy = -1;
	}
	else{
		stepy = 1;
	}
	
	if (dx < 0){
		dx = -dx;  stepx = -1;
	}
	else{
		stepx = 1;
	}

	dy <<= 1;//dy = 2*dy
	dx <<= 1;//dx = 2*dx
	
	setpix(x1,y1,color);
	
	if (dx > dy){
		int fraction = dy - (dx >> 1);
		
		while (x1 != x2){
			if (fraction >= 0){
				y1 += stepy;
				fraction -= dx;
			}
			x1 += stepx;
			fraction += dy;
			setpix(x1,y1,color);
		}
	}
	else{
		int fraction = dx - (dy >> 1);
		while (y1 != y2){
			if (fraction >= 0){
				x1 += stepx;
				fraction -= dy;
			}
			y1 += stepy;
			fraction += dx;
			setpix(x1,y1,color);
		}
	}
}
//#################################################################################################
unsigned int Ppm::scalendiff (var_pos p1, var_pos p2, var_obj obj){
        int hy = 100, wx = 100;
        var_pos pos, delta;
        double p = 0;//warscheinligkeit
        short int d = 0;
        unsigned char ti, tp;
        float scalex, scaley;

        ofstream datei1;
        datei1.open("scalendiffimage.ppm",/* ios_base::binary |*/ ios_base::out);
        datei1 << "P6" << endl << 100 << " " << 100 << endl << "255" << endl;

        ofstream datei2;
        datei2.open("scalendiffdiff.ppm",/* ios_base::binary |*/ ios_base::out);
        datei2 << "P6" << endl << 100 << " " << 100 << endl << "255" << endl;

        ofstream datei3;
        datei3.open("scalendiffskal.ppm",/* ios_base::binary |*/ ios_base::out);
        datei3 << "P6" << endl << 100 << " " << 100 << endl << "255" << endl;


        delta.x = p2.x - p1.x;
        delta.y = p2.y - p1.y;

        scalex = (float)wx / delta.x;
        scaley = (float)hy / delta.y;
//      cout << "delta.x " << delta.x << " delta.y " << delta.x << "scalex " << scalex << " scaley " << scaley << endl << flush;
        pos.y = 0;
        while(pos.y < hy){
                pos.x = 0;
                while(pos.x < wx){
                        d = 0;
                        while(d <= 2){
                        ti = obj.image[(pos.y * 100 + pos.x) * 3 + d];
                        tp = getpix((short int)(pos.x/scalex+p1.x), (short int)(pos.y/scaley+p1.y), d);
                        datei1 << ti;
                        datei3 << tp;
                        datei2 << (ti <= tp) ? (tp - ti) : (ti - tp);
                        if(ti != 255){
                                p += (ti <= tp) ? (tp - ti) : (ti - tp);
                        }

                        d++;
                        }
                pos.x++;
                }
        pos.y++;
        }
datei1.close();
datei2.close();
datei2.close();
return(p);
}
//#################################################################################################
bool Ppm::learnobj(void){
	char wahl;
	unsigned char d = 0;
	ofstream datei, datei1;
	var_obj obj;
	struct var_keyp *nextkey;
	struct var_pos pos, p1, p2, delta;
	int hy = 100, wx = 100;
	float scalex, scaley;
// 	nextkey = obj.key;
	nextkey = &obj.key;
	p1 = filter.p2;
	p2 = filter.p1;


// 	filter.color = key.color;
	filter.colorab.r = 50;
	filter.colorab.g = 50;
	filter.colorab.b = 50;

	cout << "Bitte Objektname eingeben" << endl << flush;
	cin >> obj.name;
	
	while(true){
		cout << "Bitte x-Komponente der Keypoint-Position eingeben" << endl << flush;
		cin >> pos.x;
		cout << "Bitte y-Komponente der Keypoint-Position eingeben" << endl << flush;
		cin >> pos.y;
		filter.color = getpix(pos);;
		fillmo(pos);
		if(tempvars.p1.x < p1.x){p1.x = tempvars.p1.x;}
		if(tempvars.p1.y < p1.y){p1.y = tempvars.p1.y;}
		if(tempvars.p2.x > p2.x){p2.x = tempvars.p2.x;}
		if(tempvars.p2.y > p2.y){p2.y = tempvars.p2.y;}
		tempvars.pos.x = (short int) tempvars.x / tempvars.count;
		tempvars.pos.y = (short int) tempvars.y / tempvars.count;
// 		setpix(tempvars.pos, 0, 0, 255);
// 		setpix(tempvars.p1, 0, 0, 255);
// 		setpix(tempvars.p2, 0, 0, 255);

		*nextkey = sift(tempvars.pos, static_cast <unsigned char> (tempvars.p2.x - tempvars.p1.x) * 0.75, static_cast <unsigned char> (tempvars.p2.y - tempvars.p1.y) * 0.75);
		nextkey->color = filter.color;
		nextkey->next = NULL;
		cout << "Möchten sie einen weiteren Keypoint angeben?" << endl << flush;
		cin >> wahl;
		if(wahl != 'j' && wahl != 'J'){
			break;
		}
		nextkey->next = new var_keyp;
		nextkey = nextkey->next;
	}

// 	obj.image = new unsigned char[hy * wx * 3];

	datei.open(obj.name,/* ios_base::binary |*/ ios_base::out);
	datei1.open("out.ppm",/* ios_base::binary |*/ ios_base::out);
	datei << obj.name << endl;
	datei1 << "P6" << endl << 100 << " " << 100 << endl << "255" << endl;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;

	scalex = (float)wx / delta.x;
	scaley = (float)hy / delta.y;
// 	cout << "delta.x " << delta.x << " delta.y " << delta.x << "scalex " << scalex << " scaley " << scaley << endl << flush;
	pos.y = 0;
	while(pos.y < hy){
		pos.x = 0;
		while(pos.x < wx){
			d = 0;
			while(d < 3){
				datei << getpix((short int)(pos.x / scalex + p1.x), (short int)(pos.y / scaley + p1.y), d);
				datei1 << getpix((short int)(pos.x / scalex + p1.x), (short int)(pos.y / scaley + p1.y), d);
				d++;
			}
			pos.x++;
		}
		pos.y++;
	}

	nextkey = &obj.key;
	datei << endl; 

	while(nextkey){
		datei << nextkey->color.r 
				<< nextkey->color.g 
				<< nextkey->color.b;

		datei << nextkey->key[0] 
				<< nextkey->key[1] 
				<< nextkey->key[2] 
				<< nextkey->key[3] 
				<< nextkey->key[4] 
				<< nextkey->key[5] 
				<< nextkey->key[6] 
				<< nextkey->key[7] 
				<< nextkey->ori;
		nextkey = nextkey->next;
	}
	datei.close();
	datei1.close();
	return(true);
} 
