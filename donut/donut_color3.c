#include<stdio.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<stdlib.h>

#define WIDTH 80	
#define HEIGHT 40

#define THETA_SPACING 0.04
#define PHI_SPACING 0.01

#define R1 1
#define R2 2
#define K2 5

#define K1 (WIDTH * 2.3f * K2) / (8*(R1+R2))

int main(){
	system("cls");
	float A=0.0f,B=0.0f;
	for(;;){
		//printf("\x1b[2J");
		char b[WIDTH * HEIGHT];
		float z[WIDTH * HEIGHT];

		memset(b,32,WIDTH * HEIGHT);
		memset(z,0,WIDTH * HEIGHT * sizeof(float));

		float cosA = cos(A),
		      sinA = sin(A),
		      cosB = cos(B),
		      sinB = sin(B);
	
		for(float theta = 0.0f; theta < 2 * M_PI; theta += THETA_SPACING){
			for(float phi = 0.0f; phi < 2 * M_PI; phi += PHI_SPACING){
				float cosT = cos(theta),
				      sinT = sin(theta),
			      	      cosP = cos(phi),
				      sinP = sin(phi);
				float circle_x = R2 + ( R1 * cosT );
				float circle_y = R1 * sinT;

				float x = circle_x * ((cosP*cosB)-(sinP*sinA*sinB)) + ( circle_y*cosA*sinB);
				float y = (-circle_x) * ((cosP*sinB)+(sinP*sinA*cosB)) + ( circle_y*cosA*cosB);
				float z_val = K2 - (cosA*(circle_x)*sinP) - (circle_y*sinA);
				float ooz = 1/z_val;
	
				int xp = (int) ((WIDTH/2) + K1*ooz*x);
				int yp = (int) ((HEIGHT/2) + (K1*ooz*y)*0.55f);
	
				float L = (cosP*cosT*sinB) + (cosA*cosT*sinP) + (sinA*sinT) + cosB*((cosA*sinT)-(cosT*sinA*sinP));
				
				if(L > 0){
					int o = yp * WIDTH + xp;
					if(xp>=2 && xp< WIDTH-2 && yp>=1 && yp<HEIGHT-1 && ooz > z[o]){
						z[o] = ooz;
						int lum_index = L*8;
						if(lum_index >=0 && lum_index < 12)
							b[o] = ".,-~:;=!*#$@"[lum_index];
					}
				}	
		
			}
		}
		
		//printf("\x1b[2J");
		//const int colors[] = {31,33,32,36,34,35};

		printf("\x1b[H");
		int color_offset = (int)( A * 10 ) % 6;
		
		for(int k=0; k<WIDTH*HEIGHT; k++){
			if(k % WIDTH){
				int color = 31 + (color_offset + (k/WIDTH)) %6;
				//putchar(k % WIDTH ? b[k] : '\n');
				printf("\x1b[%dm%c",color, b[k]);
			}else{
				printf("\n");
			}
		}
		
		A += 0.08;
		B += 0.04;
		Sleep(5);
	}
	return 0;
}

