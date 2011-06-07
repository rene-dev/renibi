#include "alles.h"
var_ppm * deep(var_ppm * ppml, var_ppm * ppmr, var_filterops ops){
	var_ppm * templ = new var_ppm;
	var_ppm * tempr = new var_ppm;
	var_ppm * out = new var_ppm;
	var_pos pos = ops.p1;
	int k = 0, j = 0, min, temp;
	while(pos.y < ops.p2.y){
		pos.x = ops.p1.x;
		while(pos.x < ops.p2.x){
			k = 0;
			while(k < 4){
				templ->pix[pos.x][pos.y][k] = (unsigned char) (128 - ppml->pix[pos.x - 1][pos.y][k] + ppml->pix[pos.x + 1][pos.y][k]);
				
				tempr->pix[pos.x][pos.y][k] = (unsigned char) (128 - ppmr->pix[pos.x - 1][pos.y][k] + ppmr->pix[pos.x + 1][pos.y][k]);

				k++;
			}
			pos.x++;
		}
		pos.y++;
	}

	pos = ops.p1;

	while(pos.y < ops.p2.y){
		pos.x = ops.p1.x;
		while(pos.x < (ops.p2.x - ops.max)){
			k = 0;
			min = 1000;
			temp = 0;
			while(k < 4){
				j = 0;
// 				temp = 0;
// 				min = 1000;
				while(j <= ops.max){

					if(min >(/*(templ->pix[pos.x + j][pos.y][k] - tempr->pix[pos.x + 
						j][pos.y][k]) + */(ppml->pix[pos.x + j][pos.y][k] - 	
						ppmr->pix[pos.x + j][pos.y][k])))
					{
						min = (/*(templ->pix[pos.x + j][pos.y][k] - 		
						tempr->pix[pos.x + j][pos.y][k]) + */(ppml->pix[pos.x +
						j][pos.y][k] - ppmr->pix[pos.x + j][pos.y][k]));

						temp = j;
					}
					j++;
				}
// debug(__FILE__, __LINE__, "x", pos.x);
// debug(__FILE__, __LINE__, "y", pos.y);
// debug(__FILE__, __LINE__, "j", temp);
				out->pix[pos.x][pos.y][3] = (unsigned char) temp * 5;
				k++;
			}
			pos.x++;
		}
		pos.y++;
	}


	return(out);
}
