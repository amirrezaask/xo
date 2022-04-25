#include <stdio.h>
#include <SDL2/SDL.h>
SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL;
SDL_Surface* imgSurface = NULL;
SDL_Texture* imgTexture = NULL;
SDL_Rect imgRect;
SDL_Event event;
unsigned int turn = 0;
///////////////////////////////////////
//Functions
void lose(){
imgSurface = SDL_LoadBMP("/Users/amirreza/src/github.com/amirrezaask/xo/assets/lose.bmp");
		imgTexture = SDL_CreateTextureFromSurface(mainRenderer,imgSurface);
		imgRect.y = 0;
		imgRect.x = 0;
		imgRect.w = 600;
		imgRect.h = 600;
		SDL_RenderCopy(mainRenderer,imgTexture,NULL,&imgRect);
		
		SDL_RenderPresent(mainRenderer);
		 SDL_Delay(6000);
}
void circle(int x,int y){

		imgSurface = SDL_LoadBMP("/Users/amirreza/src/github.com/amirrezaask/xo/assets/circle.bmp");
		imgTexture = SDL_CreateTextureFromSurface(mainRenderer,imgSurface);
		imgRect.y = y;
		imgRect.x = x;
		imgRect.w = 140;
		imgRect.h = 140;
		SDL_RenderCopy(mainRenderer,imgTexture,NULL,&imgRect);
		SDL_RenderPresent(mainRenderer);


}
void cross(int x,int y){

		imgSurface = SDL_LoadBMP("/Users/amirreza/src/github.com/amirrezaask/xo/assets/cross.bmp");
		imgTexture = SDL_CreateTextureFromSurface(mainRenderer,imgSurface);
		imgRect.y = y;
		imgRect.x = x;
		imgRect.w = 140;
		imgRect.h = 140;
		SDL_RenderCopy(mainRenderer,imgTexture,NULL,&imgRect);
		SDL_RenderPresent(mainRenderer);
}

//Check if game has winner
int win(const int board[9]) {

    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}
//minimax function >> recursive

int minimax(int board[9], int player) {

    int winner = win(board);
    if(winner != 0) return winner*player;
	
	//printf("\n player = %d\n",player);
	
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int thisScore = -minimax(board, player*-1);
            //printf("thisScore = %d\n",thisScore);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}

//only show circle in the place
int CpuAct(int final_move){  
   	switch(final_move){
   	case 0:
   		circle(0,0);
   		//turn++;
   		return 0;
   	case 1:
   		circle(200,0);
   		//turn++;
		return 0;   		
   	case 2:
   		circle(400,0);
   		//turn++;
   		return 0;
   	case 3:
   		circle(0,200);
   		//turn++;
   		return 0;
   	case 4:
   		circle(200,200);
   		//turn++;
   		return 0;
   	case 5:
   		circle(400,200);
   		//turn++;
   		return 0;
   	case 6:
   		circle(0,400);
   		//turn++;
   		return 0;
   	case 7:
   		circle(200,400);
   		//turn++;
   		return 0;
  	case 8:
  		circle(400,400)	;
  		//turn++;	
  		return 0;
   
   	}
   }
void salam() {
    printf("salam");
}
//Making A Move Using minimax function
void cpuMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            //printf("\n tempscore = %d\n",tempScore);
            //for (int g = 0;g <9;g++)
		 	//	printf("%d",board[g]);		 
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    board[move] = 1;
    //printf("\nCPU  >> %d\n",move);	
	CpuAct(move);
	 }

//End Of Functions	

//************************************************************
int run(){
int player = 1;
int board[9] = {0,0,0,0,0,0,0,0,0};
//Create A Window
window = SDL_CreateWindow("TIC TAC TOE ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,600,600,0);
//Create A Renderer Acts Like A White Paper
mainRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
//Creating A Surface >> Address To Photo In HardDrive
imgSurface = SDL_LoadBMP("/Users/amirreza/src/github.com/amirrezaask/xo/assets/board.bmp");
//Now Make A Texture >> Enter The Photo To GPU
imgTexture = SDL_CreateTextureFromSurface(mainRenderer,imgSurface);

imgRect.y = 0;
imgRect.x = 0;
imgRect.w = 600;
imgRect.h = 600;

SDL_RenderCopy(mainRenderer,imgTexture,NULL,&imgRect);

game:
		 //printf("\nplayer  >> %d\n",player);
		 //printf("\nturn  >> %d\n",turn);
		 //for (int g = 0;g <9;g++)
		 //	printf("%d",board[g]);
		 	
		 if((turn+player) % 2 == 0){
		 		if(win(board) == 0 && turn == 8){
					printf("\n");
					printf("\nBazi Mosavi Shod !!\n");
					//lose();
					return 0;
						}
				else if(win(board) == 1 && turn == 8){
						printf("\n");
						printf("\nBakhti Jooje !!\n");
						lose();
						//SDL_Delay(5000);
						return 0;
							}
				else if(win(board) == -1 && turn == 8){
					printf("\n");
					printf("\nBordi\n");
					//lose();
					return 0;
					}
				cpuMove(board);
				turn++;
				goto game;
				}
				else{
				if(win(board) == 0 && turn == 8){
					printf("\n");
					printf("Bazi Mosavi Shod !!");
					//lose();
					return 0;
					}					
					else if(win(board) == 1 && turn == 8){
							printf("\n");
							printf("Bakhti Jooje !!");
							lose();
							return 0;
						}
					else if(win(board) == -1 && turn == 8){
						printf("Bordi");
						//lose();
						return 0;
						}
		while (1){
		SDL_RenderPresent(mainRenderer);

			while(SDL_PollEvent(&event) != 0)
				{
	
				if (event.type == SDL_QUIT){
						printf("\nQUITING APPLICATION\n");
						return 0;
						}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
					{	
						int x = event.motion.x;
						int y = event.motion.y;
				
						 
						if(x < 200 && y < 200){
								if (board[0] == 0){
										cross(0,0);
										board[0] = -1;
										turn++;
										goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
								} 
									
	
								}
						else if(x> 200 && x < 400 && y < 200){
								if (board[1] == 0){
								cross(200,0);
								board[1] = -1;
								turn++;
								goto game;
								}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
					
								}
						else if(x > 400 && x < 600 && y < 200 ){
								if (board[2] == 0){
								cross(400,0);
								board[2] = -1;
								turn++;
								goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
								} 
								}
						else if(x < 200 && y < 400 && y > 200){
								if (board[3] == 0){
								cross(0,200);
								board[3] = -1;
								turn++;
								goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
								}
					
						else if (x > 200 && x < 400 && y > 200 && y < 400){
								if (board[4] == 0){
								cross(200,200);
								board[4] = -1;
								turn++;
								goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
								}
						else if (x > 400 && x < 600 && y > 200 && y < 400){
								if(board[5] == 0){
								cross(400,200);
								board[5] = -1;
								turn++;
								goto game;
									}
								else
								{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
								}
						else if(x < 200 && y < 600 && y > 400){
								if(board[6] == 0){
								cross(0,400);
								board[6] = -1;
								turn++;
								goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
								}
						else if (x > 200 && x < 400 && y > 400 && y < 600 ){
								if(board[7] == 0){
								cross(200,400);
								board[7] = -1;
								turn++;
								goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
								}		
						else if (x >400 && x < 600 && y >400 && y < 600){
							if(board[8] == 0){
							cross(400,400);
							board[8] = -1;
							turn++;
							goto game;
									}
								else{
								printf("Khoone Ye Tekrari Nemishe zad !!");
								goto game;
									} 
								}
						}
					}

				}	



	
		}
	
}
// ***********************************************************






