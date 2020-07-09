/*
 * Zeynep Ülkü Kılıç
 * 
 * main.c
 * the controller for the program,
 *
 *  Created on: Nov 26, 2018
 *      Author: adaskin
 */

/*screen size */
#define W_HEIGHT 200
#define W_WIDTH 200


int done = 0; 			/* devam mi tamam mi?							*/
int polygonDone = 0; 	/* polygonun alinip alinmadigini kontrol ediyor	*/

/*functions in sdlView*/
void drawPolygon();
int showArea(double);
int quitSDLAll();
int initSDLWindow(int width, int height);
int checkMouseEvents();

/*functions in polygon.c (the model)*/
int generateCoeffs();
double findArea(double width, double height);
int resetAll();

int main(int argc, char* argv[]) {
	initSDLWindow(W_WIDTH, W_HEIGHT);

	while (!done) {
		checkMouseEvents(); 		/*	listen and handle mouse clicks	*/
		drawPolygon();				/*	drawPolygon						*/
		if(polygonDone){

			/* y = mx +b tum kenarlar icin m ve b degerlerini bul	*/
			generateCoeffs();
			/*alni hesapla*/
			double area = findArea(W_WIDTH, W_HEIGHT);

			/*alani messagebox ile goster*/
			showArea(area);

			/*resetlenebilecekleri resetle, free allocated memory*/
			resetAll();

			/*yeni polygon icin*/
			polygonDone = 0;
		}

	}

	quitSDLAll();
	return 0;
}
