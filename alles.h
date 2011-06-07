#ifndef _allesh_
#define _allesh_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <linux/videodev.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>
#include <new>

#include "config"

using namespace std;
/*
aray[x][y]

\01234 x
0#####
1#####
2#####
3#####
4#####
y
*/
struct var_matrix{
	char kern[3][3];
	short int div;
};
	
struct var_color{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct var_pos{//variable für positionen
	short int x;
	short int y;
	struct var_pos *next;
};

struct var_keyp{
	var_color color;
	unsigned char x, y, ori; //Hauptrichtung
	float scale;
	unsigned char key[8];//histogramm
	struct var_keyp *next;
};

struct var_obj{
	char name[21];
	struct var_keyp key;
	unsigned char *image;
	struct var_pos *pos;
	struct var_obj *next;
};

struct var_area{
	char name[21];
	struct var_pos p1, p2;
	struct var_area *next;
};

struct var_karte{
	char name[21];
	unsigned char *karte;
	struct var_pos ich;
	struct var_obj *obj;
	struct var_area *area;
};

class Ppm{
	private:
		unsigned char *pix;
		
		unsigned char *temp;
		var_color color;
		bool fill(short int , var_pos, var_color, unsigned char/*, int &, int &, int &*/);
		bool fillmo(var_pos, unsigned char);
		bool match1objkey(var_keyp);
		struct tempvar{
			int count, x, y;
			var_pos pos, p1, p2;
			struct var_keyp key;
			struct var_pos keypos, *nextkeypos;
		} tempvars;

	public:
		var_keyp keypoint;
		short int h, w; //Höhe, Breite
		unsigned char t; //Tiefe

		class Ppm * next;

		struct  filterops{
			short int area;
			unsigned char tresh, tresh2;
			struct var_color treshcolor, treshcolor2;
			short int min;
			short int max;
			char matrix[3][3];
			float matrixdiv;
			struct var_color colorab;
			struct var_color color;
			struct var_pos p1, tp1;
			struct var_pos p2, tp2; //Bereich von obj in pix
		} filter;
		
		//##########	Prototypen	##########
		float			minrgb		(float, float, float);
		float			maxrgb		(float, float, float);
		var_color	rgb2hsv		(var_color);
		var_color	hsv2rgb		(var_color);
		bool			rgb2hsvpix	(void);
		bool			hsv2rgbpix	(void);

		unsigned
		char*			openimage	(char *);
		bool			openppm		(char *);
		bool 			learnobj(void);
		bool			save			(char *);
		bool			savesw		(char *);
		bool			makesw		(void);
		bool			makesw		(unsigned char);

		
		unsigned 
		int			scalendiff	(var_pos, var_pos, var_obj);

		bool			faltungpix	(void);
		bool			faltungtemp	(void);
		bool			setmatrix	(unsigned char);
		bool			rgb2hsv		(void);
		bool			settemp		(unsigned char val);

		bool			diffpix		(void);
		bool			diffpix2		(void);
		bool			difftemp		(void);
		bool			difftemp2	(unsigned char);


		var_keyp		sift			(var_pos, unsigned char, unsigned char);

		unsigned
		short
		int			matchkey		(var_keyp, var_keyp);
		unsigned 
		int			matchobj		(var_obj obj);
		bool			fill			(unsigned char, var_pos);
		var_pos		fill2			(unsigned char, var_pos);
		bool			fill2			(short int, var_pos, var_color, unsigned char);
		bool			searchpix	(unsigned char);

		bool			treshpix		(void);
		bool			treshpix2	(void);
		bool			treshpix3	(void);
		bool			treshpix4	(void);
		bool			treshpix		(unsigned char, unsigned char);
		bool			treshpix2	(unsigned char, unsigned char);
		bool			treshpix3	(unsigned char, unsigned char);
		bool			treshpix4	(unsigned char, unsigned char);
		bool			treshtemp	(unsigned char);
		bool			treshtemp2	(unsigned char);
		bool			treshtemp3	(unsigned char);
		bool			treshtemp4	(unsigned char);

		bool			skeletpix	(void);
		bool			skelettemp	(unsigned char);
		void			line			(short int, short int, short int, short int);
		var_obj		openobj		(char *);
		//##########	Funktionen	##########

		inline unsigned char getsw(short int tx, short int ty){
			return((unsigned char)(getpix(tx, ty, 0) + getpix(tx, ty, 1) + getpix(tx, ty, 2)) / 3);
		}

		inline bool setpix(struct var_pos pos, struct var_color val){
			if(pos.x < 0 || pos.x > w || pos.y < 0 || pos.y > h){
				return(false);
			}
			pix[(pos.y * w + pos.x) * t + 0] = val.r;
			pix[(pos.y * w + pos.x) * t + 1] = val.g;
			pix[(pos.y * w + pos.x) * t + 2] = val.b;
			return(true);
		}

		inline bool setpix(struct var_pos pos, unsigned char r, unsigned char g,  unsigned char b){
			if(pos.x < 0 || pos.x > w || pos.y < 0 || pos.y > h){
				return(false);
			}
			pix[(pos.y * w + pos.x) * t + 0] = r;
			pix[(pos.y * w + pos.x) * t + 1] = g;
			pix[(pos.y * w + pos.x) * t + 2] = b;
			return(true);
		}

		inline bool setpix(struct var_pos pos, unsigned char d, unsigned char val){
			if(pos.x < 0 || pos.x > w || pos.y < 0 || pos.y > h){
				return(false);
			}
			pix[(pos.y * w + pos.x) * t + d] = val;
			return(true);
		}

		inline bool setpix(short int x, short int y, struct var_color val){
			if(x < 0 || x > w || y < 0 || y > h){
				return(false);
			}
			pix[(y * w + x) * t + 0] = val.r;
			pix[(y * w + x) * t + 1] = val.g;
			pix[(y * w + x) * t + 2] = val.b;
			return(true);
		}

		inline bool setpix(short int x, short int y, unsigned char r, unsigned char g,  unsigned char b){
			if(x < 0 || x > w || y < 0 || y > h){
				return(false);
			}
			pix[(y * w + x) * t + 0] = r;
			pix[(y * w + x) * t + 1] = g;
			pix[(y * w + x) * t + 2] = b;
			return(true);
		}

		inline bool setpix(short int x, short int y, unsigned char d, unsigned char val){
			if(x < 0 || x > w || y < 0 || y > h){
				return(false);
			}
			pix[(y * w + x) * t + d] = val;
			return(true);
		}

		inline var_color getpix(struct var_pos pos){
			color.r = pix[(pos.y * w + pos.x) * t + 0];
			color.g = pix[(pos.y * w + pos.x) * t + 1];
			color.b = pix[(pos.y * w + pos.x) * t + 2];
			return(color);
		}

		inline var_color getpix(short int x, short int y){
			color.r = pix[(y * w + x) * t + 0];
			color.g = pix[(y * w + x) * t + 1];
			color.b = pix[(y * w + x) * t + 2];
			return(color);
		}

		inline unsigned char getpix(struct var_pos pos, unsigned char d){
			return(pix[(pos.y * w + pos.x) * t + d]);
		}

		inline unsigned char getpix(short int x, short int y, unsigned char d){
			return(pix[(y * w + x) * t + d]);
		}

		inline bool settemp(struct var_pos pos, unsigned char val){
			if(pos.x < 0 || pos.x > w || pos.y < 0 || pos.y > h){
				return(false);
			}
			temp[pos.y * w + pos.x] = val;
			return(true);
		}

		inline bool settemp(short int x, short int y, unsigned char val){
			if(x < 0 || x > w || y < 0 || y > h){
				return(false);
			}
			temp[y * w + x] = val;
			return(true);
		}

		inline unsigned char gettemp(struct var_pos pos){
			return(temp[pos.y * w + pos.x]);
		}

		inline unsigned char gettemp(short int x, short int y){
			return(pix[y * w + x]);
		}

		inline bool erkannt(struct var_pos pos, var_color color){
			if(
				getpix(pos, 0) > color.r + filter.colorab.r ||
				getpix(pos, 0) < color.r - filter.colorab.r ||
				getpix(pos, 1) > color.g + filter.colorab.g ||
				getpix(pos, 1) < color.g - filter.colorab.g ||
				getpix(pos, 2) > color.b + filter.colorab.b ||
				getpix(pos, 2) < color.b - filter.colorab.b
			){return (false	);}
			else{return (true);}
		}

		inline bool erkannt(struct var_pos pos){
			if(
				getpix(pos, 0) > filter.color.r + filter.colorab.r ||
				getpix(pos, 0) < filter.color.r - filter.colorab.r ||
				getpix(pos, 1) > filter.color.g + filter.colorab.g ||
				getpix(pos, 1) < filter.color.g - filter.colorab.g ||
				getpix(pos, 2) > filter.color.b + filter.colorab.b ||
				getpix(pos, 2) < filter.color.b - filter.colorab.b
			){return (false	);}
			else{return (true);}
		}

		
		bool createnext(short int x, short int y, short int d){
			next = new Ppm(x, y, d);
			return(true);
		}

		bool copy(void){
			for(int i = 0;i <= h * w * t; i++){next->pix[i] = pix[i];}
			for(int i = 0;i <= h * w; i++){next->temp[i] = temp[i];}
			next->h = h;
			next->w = w;
			next->t = t;
			return(true);
		}

		bool recopy(void){
			for(int i = 0;i <= h * w * t; i++){pix[i] = next->pix[i];}
			for(int i = 0;i <= h * w; i++){temp[i] = next->temp[i];}
			h = next->h;
			w = next->w;
			t = next->t;
			return(true);
		}


		//Konstruktor
		Ppm(short int x, short int y, unsigned char d){
			h = y;
			w = x;
			t = d;
			pix = new unsigned char [(x+1) * (y+1) * d];
			temp = new unsigned char [(x+1) * (y+1)];
			for(int i = 0;i <= h * w * t; i++){pix[i] = 0;}
			for(int i = 0;i <= h * w; i++){temp[i] = 0;}
			
			tempvars.count = 0;
			tempvars.x= 0;
			tempvars.y= 0;
			tempvars.pos.x= 0;
			tempvars.pos.y= 0;
			tempvars.p1.x= 0;
			tempvars.p1.y= 0;
			tempvars.p2.x= 0;
			tempvars.p2.y= 0;

	

		}
		//Destruktor
		~Ppm(void){
			delete []pix;
			delete []temp;
		}
};//ende von class Ppm

inline void debug(string, int, string, int);//debug(=

#include "inline.cpp"

#endif
