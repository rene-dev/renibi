// inline bool erkannt(var_ppm * ppm, var_pos pos, var_color color, var_color colorab){
// 	if(
// 	ppm->pix[pos.x][pos.y][0] > color.r + colorab.r ||
// 	ppm->pix[pos.x][pos.y][0] < color.r - colorab.r ||
// 	ppm->pix[pos.x][pos.y][1] > color.g + colorab.g ||
// 	ppm->pix[pos.x][pos.y][1] < color.g - colorab.g ||
// 	ppm->pix[pos.x][pos.y][2] > color.b + colorab.b ||
// 	ppm->pix[pos.x][pos.y][2] < color.b - colorab.b
// 	                                        
// 	){
// 		return(false);
// 	}
// 	else{
// 		return(true);
// 	}
// }

inline void debug(string file, int pos, string text, int wert){// inline heist füge code  ein
	if(DEBUG == 2){
		cout << text << endl << flush;
	}
	
	if(DEBUG == 1){
		cout << text << ": " << wert << endl << flush;
	}
	
	if(DEBUG == 3){
		cout << "Zeile: "  << pos << " in Datei: " << file << "# "<< text << ": " << wert << endl << flush;
	}
	
	if(DEBUG == 4){
		cout << "Zeile: "  << pos << " in Datei: " << file << endl << flush;
	}
}
