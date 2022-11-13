/*----------游戏主体类----------*/

class Game{
public :
	bool agree(bool isR,bool black);	//悔棋确认函数
	void Add(int i,int j);//添加权值
	bool PlayGame1();						//单人游戏主体函数
	bool PlayGame2();						//双人游戏主体函数
	void chessboard(bool isR, bool sound );	//棋盘函数
};


//悔棋确认函数
bool agree(bool isR,bool black)	{
	int k,YES1 , YES2 , NO1 , NO2 ;
	IMAGE Back[2];// 定义 IMAGE 对象
	loadimage(&Back[0],"static\\image\\玩家1请求悔棋.png") ;
	loadimage(&Back[1],"static\\image\\玩家2请求悔棋.png") ;
	if(!isR){
		if( black ){
			putimage( 910 , 400 , &Back[1]); //玩家2请求悔棋，是否同意？
			YES1 = 'Y' ; YES2 = 'y' ;
			NO1 = 'N' ; NO2 = 'n' ;
		}else{
			putimage( 910 , 400 , &Back[0]); //玩家1请求悔棋，是否同意？
			YES1 = 55 ; YES2 = 55 ;
			NO1 = 57 ; NO2 = 57 ;
		}
		k=_getch();
		if(YES1==k || YES2==k ){
			if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
			fillrectangle(910 , 400,1155, 520);//遮住悔棋提示
			pStack->pop()  ; 	//出栈
			if(black){	
				//轮到玩家2操作
				putimage( 909 , 30 , &Player[1][1]); //小李白选中
				putimage( 909 , 600 , &Player[0][0]); //小韩信非选
			}else{
				//轮到玩家1操作
				putimage( 909 , 600 , &Player[0][1]); //小韩信选中
				putimage( 909 , 30 , &Player[1][0]); //小李白非选	
			}
			black= ! black; //切换玩家
		}
		else if(NO1==k || NO2==k ){
			if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
			fillrectangle(910 , 400,1155, 520);//遮住悔棋提示
		}else{
			black=agree( isRobot,black ) ;
		}
		return black ;
	}else{
		if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
		fillrectangle(910 , 400,1155, 520);//遮住悔棋提示
		pStack->pop()  ; 	
		pStack->pop()  ; 	
		putimage( 909 , 600 , &Player[0][1]); //小韩信选中
		putimage( 909 , 30 , &Player[1][0]); //小李白非选	
		return !black ;
	}
}


//添加权值
void Add(int x,int y){
	int i=x*60+30;
	int j=y*60+30;
	int k=0 ;
	int num_black=0;//计数器置0
	int num_white=0;
	//正对角线判断
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右下方有无相邻白色子
		if ( pStack->stackTraverse( i+60*k, j+60*k , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左上方有无相邻白色子
				if ( pStack->stackTraverse( i-60*k, j-60*k , false) ){
						num_white++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_white){
	case 0:	winku[x][y]=0;break;
	case 1:winku[x][y]=5;break;
	case 2:winku[x][y]=125;break;
	case 3:winku[x][y]=3125;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]=78125;break;
	default:winku[x][y]=0;break;
	}
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右下方有无相邻黑色子
		if ( pStack->stackTraverse( i+60*k, j+60*k , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左上方有无相邻黑色子
				if ( pStack->stackTraverse( i-60*k, j-60*k , true) ){
						num_black++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_black){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=1;break;
	case 2:winku[x][y]+=25;break;
	case 3:winku[x][y]+=625;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=15625;break;
	default:winku[x][y]+=0;break;
	}
	//反对角线判断
	num_white=0;//计数器置0
	num_black=0;
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右上方有无相邻白色子
		if ( pStack->stackTraverse( i+60*k, j-60*k , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左下方有无相邻白色子
				if ( pStack->stackTraverse( i-60*k, j+60*k , false) ){
						num_white++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_white){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=5;break;
	case 2:winku[x][y]+=125;break;
	case 3:winku[x][y]+=3125;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=78125;break;
	default:winku[x][y]+=0;break;
	}
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右上方有无相邻黑色子
		if ( pStack->stackTraverse( i+60*k, j-60*k , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左下方有无相邻黑色子
				if ( pStack->stackTraverse( i-60*k, j+60*k , true) ){
						num_black++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_black){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=1;break;
	case 2:winku[x][y]+=25;break;
	case 3:winku[x][y]+=625;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=15625;break;
	default:winku[x][y]+=0;break;
	}
	//横向判断
	num_white=0;//计数器置0
	num_black=0;
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右方有无相邻白色子
		if ( pStack->stackTraverse( i+60*k, j , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左方有无相邻白色子
				if ( pStack->stackTraverse( i-60*k, j , false) ){
						num_white++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_white){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=5;break;
	case 2:winku[x][y]+=125;break;
	case 3:winku[x][y]+=3125;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=78125;break;
	default:winku[x][y]+=0;break;
	}
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右方有无相邻黑色子
		if ( pStack->stackTraverse( i+60*k, j , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左方有无相邻黑色子
				if ( pStack->stackTraverse( i-60*k, j , true) ){
						num_black++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_black){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=1;break;
	case 2:winku[x][y]+=25;break;
	case 3:winku[x][y]+=625;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=15625;break;
	default:winku[x][y]+=0;break;
	}
	//纵向判断
	num_white=0;//计数器置0
	num_black=0;
	for ( k=1 ; k<5 ; k++  ){//判断当前落子上方有无相邻白色子
		if ( pStack->stackTraverse( i, j-60*k , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子下方有无相邻白色子
				if ( pStack->stackTraverse( i, j+60*k , false) ){
						num_white++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_white){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=5;break;
	case 2:winku[x][y]+=125;break;
	case 3:winku[x][y]+=3125;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=78125;break;
	default:winku[x][y]+=0;break;
	}
	for ( k=1 ; k<5 ; k++  ){//判断当前落子上方有无相邻黑色子
		if ( pStack->stackTraverse( i, j-60*k , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子下方有无相邻黑色子
				if ( pStack->stackTraverse( i, j+60*k , true) ){
						num_black++ ;
				}else break;
			}
			break ;
		}
	}
	switch(num_black){
	case 0:	winku[x][y]+=0;break;
	case 1:winku[x][y]+=1;break;
	case 2:winku[x][y]+=25;break;
	case 3:winku[x][y]+=625;break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:winku[x][y]+=15625;break;
	default:winku[x][y]+=0;break;
	}
}




//单人游戏主体函数
bool PlayGame1(){
	int i=7 , j=7 , k=1;
	int X , Y ;
	bool black=true ;
	IMAGE img,img2,end;// 存放光标位置恢复图（结束提示图也用了一下）
	IMAGE Win[2];// 存放胜利提示图
	loadimage(&Win[0],"static\\image\\玩家1胜利.png") ;
	loadimage(&Win[1],"static\\image\\玩家2胜利.png") ;
	loadimage(&Player[0][0],"static\\image\\小韩信非选.png") ;
	loadimage(&Player[0][1],"static\\image\\小韩信选中.png") ;
	loadimage(&Player[1][0],"static\\image\\小李白非选.png") ;
	loadimage(&Player[1][1],"static\\image\\小李白选中.png") ;
	putimage( 909 , 600 , &Player[0][1]); //小韩信选中
	putimage( 909 , 30 , &Player[1][0]); //小李白非选

	//**控制光标移动**//
	do{
		X=(i%15)*60+30 ;  
 		Y=(j%15)*60+30 ;
		getimage(&img, X-30, Y-30, X+30, Y+30);	// 将当前界面保存区域至 img 对象
		setlinestyle(PS_SOLID, 2);		//画实线，宽度为2像素
		setcolor( RED );			//设为红色
		line(X-28, Y-29, X-28, Y-18 );
		line(X-29, Y-28, X-18, Y-28 );
		line(X-28, Y+28, X-28, Y+18 );
		line(X-28, Y+28, X-18, Y+28 );
		line(X+28, Y+28, X+28, Y+18 );
		line(X+28, Y+28, X+18, Y+28 );
		line(X+28, Y-29, X+18, Y-28 );
		line(X+29, Y-28, X+28, Y-18 );
		setlinecolor( WHITE );			//设线条为白色
		setfillcolor( WHITE );				//设填充为白色

		if(27==k){ //按ESC
			if(Sound ) 	mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
			loadimage(&end,"static\\image\\是否退出游戏.png") ;
			putimage( 910 , 400, &end); //是否退出游戏?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k)
			{	k=_getch();
				switch ( k ){//记录按键
				case 'Y' :
				case 'y' : 	
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					pStack->clearStack();//清空栈
					return false ;
				case 'N':
				case 'n' :	
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					fillrectangle(910 , 400,1155, 520 ) ; 
					break ; //遮住退出提示
				default :  break ;
				}	
			}
		}

		if(9==k) {//按TAB
			if(Sound ) 	mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
			loadimage(&end,"static\\image\\是否重新开始.png") ;
			putimage( 910 , 400, &end); //是否重新开始?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k){
				k=_getch();
				switch ( k ){//记录按键
				case 'Y' :
				case 'y' : 	
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					pStack->clearStack();//清空栈
					chessboard( isRobot,Sound );//重新加载棋盘
					return false ;
				case 'N':
				case 'n' :	
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					fillrectangle(910 , 400,1155, 520 ) ; 
					break ; //遮住退出提示
				default :  break ;
				}
			}
		}
		//这里需要判断轮到玩家还是人机
		if(black){ //玩家1黑棋
			k=_getch();//记录按键
			putimage(X-30, Y-30, &img); ////擦掉原来的光标
			if (32==k ){  //玩家1用空格落子
				black = pStack->push( black , Coordinate ( img , X , Y ) ); //落子入栈
				if(false==black){
					winku[(X-30)/60][(Y-30)/60]=-1;
					if( pStack->isWin(  X , Y , !black )  ){	//如果获胜
						if(Sound )	 mciSendString("play static\\sound\\胜利.wav", NULL, 0, 0);//播放音效
						putimage( 910 , 400 , &Win[0]); //恭喜玩家 1获胜！
						//将权值归零
						for(int mmm=0 ; mmm<15 ; mmm++){
							for(int nnn =0 ; nnn<15 ; nnn++){
								winku[mmm][nnn]=0;
							}
						}
						k=_getch();//记录按键
						if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
						pStack->clearStack();//清空栈
						Menu *menu = new Menu();
						menu->Menuface();//返回菜单界面
						return true ;
					}
					//轮到电脑操作
					putimage( 909 , 30 , &Player[1][1]); //小李白选中
					putimage( 909 , 600 , &Player[0][0]); //小韩信非选	
				}
			}
			else if ( 'R'==k || 'r'==k ) { //玩家1按下 R 悔棋
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				if(  ! pStack->stackEmpty()	)
					agree( isRobot,black );//是否同意悔棋
			}else if('w'==k || 'W'==k) {
				 j-- ;
				if(0>j) j+=15 ;
				if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}else if('s'==k || 'S'==k) {
				j++ 	;
				if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}else if('a'==k || 'A'==k) {
				 i-- ;
				if(0>i) i+=15 ; 
				if(Sound )	mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}else if('d'==k || 'D'==k){
				i++ ; 
				if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}else ;
		}else{//人机白棋
			putimage(X-30, Y-30, &img); ////擦掉原来的光标
			int maxNum = -1;
			//给棋盘空白位置添加权值
			for(int xxx =0 ; xxx<15 ; xxx++){
				for(int yyy = 0 ; yyy<15 ; yyy++){
					if ( false==pStack->stackTraverse(( xxx*60+30), (yyy *60+30), false )  &&
						 false==pStack->stackTraverse(( xxx*60+30), (yyy *60+30), true ) ) {
						Add(xxx,yyy);
					}
				}
			}
			for(int xxx =0 ; xxx<15 ; xxx++){
				for(int yyy = 0 ; yyy<15 ; yyy++){
					if(winku[xxx][yyy]>maxNum){
						maxNum=winku[xxx][yyy];
						X=xxx*60+30;
						Y=yyy*60+30;
					}
				}
			}
			getimage(&img2, X-30, Y-30,  X+30, X+30);	// 将当前界面保存区域至 img 对象
			Sleep(100);//防止CPU占用过高
			black=pStack->push( black , Coordinate (  img2, X , Y) );//落子入栈
			if(true==black){
				winku[(X-30)/60][(Y-30)/60]=-1;
				if( pStack->isWin(  X ,  Y , !black )  ){	//如果获胜
					if(Sound )	 mciSendString("play static\\sound\\胜利.wav", NULL, 0, 0);//播放音效
					putimage( 910 , 400, &Win[1]); //恭喜玩家 2 获胜！
					for(int mmm=0 ; mmm<15 ; mmm++){//将权值归零
						for(int nnn=0 ; nnn<15 ; nnn++){
							winku[mmm][nnn]=0;
						}				
					}
					k=_getch();//记录按键
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					pStack->clearStack();//清空栈
					Menu *menu = new Menu();
					menu->Menuface();//返回菜单界面
					return true ;
				}
				//轮到电脑
				putimage( 909 , 600 , &Player[0][1]); //小韩信选中
				putimage( 909 , 30 , &Player[1][0]); //小李白非选		
			}
		}
	}while(1);
}






//双人游戏主体函数
bool PlayGame2(){
	int i=7 , j=7 , k=1;
	int X , Y ;
	bool black=true ;
	IMAGE img,end;// 存放光标位置恢复图（结束提示图也用了一下）
	IMAGE Win[2];// 存放胜利提示图
	loadimage(&Win[0],"static\\image\\玩家1胜利.png") ;
	loadimage(&Win[1],"static\\image\\玩家2胜利.png") ;
	loadimage(&Player[0][0],"static\\image\\小韩信非选.png") ;
	loadimage(&Player[0][1],"static\\image\\小韩信选中.png") ;
	loadimage(&Player[1][0],"static\\image\\小李白非选.png") ;
	loadimage(&Player[1][1],"static\\image\\小李白选中.png") ;
	putimage( 909 , 600 , &Player[0][1]); //小韩信选中
	putimage( 909 , 30 , &Player[1][0]); //小李白非选

	//**控制光标移动**//
	do
	{
		X=(i%15)*60+30 ;  
		Y=(j%15)*60+30 ;
		getimage(&img, X-30, Y-30, 60, 60);	// 将当前界面保存区域至 img 对象
		setlinestyle(PS_SOLID, 2);		//画实线，宽度为2像素
		setcolor( RED );			//设为红色
		line(X-28, Y-29, X-28, Y-18 );
		line(X-29, Y-28, X-18, Y-28 );
		line(X-28, Y+28, X-28, Y+18 );
		line(X-28, Y+28, X-18, Y+28 );
		line(X+28, Y+28, X+28, Y+18 );
		line(X+28, Y+28, X+18, Y+28 );
		line(X+28, Y-29, X+18, Y-28 );
		line(X+29, Y-28, X+28, Y-18 );
		setlinecolor( WHITE );			//设线条为白色
		setfillcolor( WHITE );			//设填充为白色
		k=_getch();//记录按键
		putimage(X-30, Y-30, &img); ////擦掉原来的光标
		if(27==k) //按ESC
		{
			if(Sound ) 	mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
			loadimage(&end,"static\\image\\是否退出游戏.png") ;
			putimage( 910 , 400, &end); //是否退出游戏?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k)
			{	k=_getch();
			switch ( k )//记录按键
			{
			case 'Y' :
			case 'y' : 	
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				pStack->clearStack();//清空栈
				return false ;
			case 'N':
			case 'n' :	
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				fillrectangle(910 , 400,1155, 520 ) ; 
				break ; //遮住退出提示
			default :  break ;
			}	
			}
		}

		if(9==k) //按TAB
		{
			if(Sound ) 	mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
			loadimage(&end,"static\\image\\是否重新开始.png") ;
			putimage( 910 , 400, &end); //是否重新开始?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k)
			{	k=_getch();
			switch ( k )//记录按键
			{
			case 'Y' :
			case 'y' : 	
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				pStack->clearStack();//清空栈
				chessboard( isRobot,Sound );//重新加载棋盘
				return false ;
			case 'N':
			case 'n' :	
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				fillrectangle(910 , 400,1155, 520 ) ; 
				break ; //遮住退出提示
			default :  break ;
			}	
			}
		}

		//这里需要判断由玩家1/2来控制
		if(black) //玩家1黑棋
		{
			if (32==k ){ //玩家1用空格落子
				black = pStack->push( black , Coordinate ( img , X , Y ) ); //落子入栈
				if( pStack->isWin(  X , Y , !black )  )	{//如果获胜
					if(Sound )	 mciSendString("play static\\sound\\胜利.wav", NULL, 0, 0);//播放音效
					putimage( 910 , 400 , &Win[0]); //恭喜玩家 1获胜！
					k=_getch();//记录按键
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					pStack->clearStack();//清空栈
					Menu *menu = new Menu();
					menu->Menuface();//返回菜单界面
					return true ;
				}
				if(false == black)
				{	//轮到玩家1操作
					putimage( 909 , 30 , &Player[1][1]); //小李白选中
					putimage( 909 , 600 , &Player[0][0]); //小韩信非选		
				}
			}
			else if ( 50 ==k  ) //玩家2按下 “2” 悔棋
			{
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				if(  ! pStack->stackEmpty()	)
					black = agree( isRobot,black );//是否同意悔棋
			}
			//玩家1用“w”，“s”，“a”，“d”控制上下左右移动光标
			else if('w'==k || 'W'==k) 
			{	 j-- ;
			if(0>j) j+=15 ;
			if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}
			else if('s'==k || 'S'==k) 
			{	j++ 	;
			if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}		
			else if('a'==k || 'A'==k) 
			{	 i-- ;
			if(i>0) i+=15 ; 
			if(Sound )	mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}
			else if('d'==k || 'D'==k)
			{	i++ ; 
			if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}
			else ;
		}
		else//玩家2白棋
		{	
			if (13==k ){	//玩家2用回车落子

				black = pStack->push( black , Coordinate ( img , X , Y ) );//落子入栈

				if( pStack->isWin(  X , Y , !black )  ){	//如果获胜
					if(Sound )	 mciSendString("play static\\sound\\胜利.wav", NULL, 0, 0);//播放音效
					putimage( 910 , 400, &Win[1]); //恭喜玩家 2 获胜！
					k=_getch();//记录按键
					if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					pStack->clearStack();//清空栈
					Menu *menu = new Menu();
					menu->Menuface();//返回菜单界面
					return true ;
				}
				if(true == black)
				{	//轮到玩家1操作
					putimage( 909 , 600 , &Player[0][1]); //小韩信选中
					putimage( 909 , 30 , &Player[1][0]); //小李白非选		
				}

			} 
			else if ( 'R'==k || 'r'==k )  //玩家1按下 R 悔棋
			{	
				if(Sound )	 mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				if(  ! pStack->stackEmpty()	)
					black = agree(isRobot, black );		//是否同意悔棋
			}
			//玩家2用“↑”，“↓”，“←”，“→”控制上下左右移动光标
			else if(72==k) 
			{	 j-- ;
			if(0>j) j+=15 ;
			if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}
			else if(80==k) 
			{	j++ 	;
			if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}		
			else if(75==k) 
			{	 i-- ;
			if(0>i) i+=15 ; 
			if(Sound )	mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}
			else if(77==k)
			{	i++ ; 
			if(Sound )	 mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
			}
			else ;
		}
	}while(1);
}

//棋盘函数
void chessboard(bool isR, bool sound ){
	isRobot = isR;//人机模式状态传入全局变量isRobot
	Sound = sound ;//音效状态传入全局变量Sound
	cleardevice();					//清空屏幕
	loadimage(0,  ("static\\image\\棋盘背景图片.jpg")	); 
	setlinestyle(PS_SOLID, 2);		//宽度为2像素
	setcolor(RGB(0, 0, 0));			//设为黑色
	for(int i = 30; i <= 900; i+=60){//画实线
		line(i, 30, i,870 );
		line(30, i, 870, i);
	}
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(455,455,445,445);
	fillrectangle(205,205,215,215);
	fillrectangle(685,205,695,215);
	fillrectangle(205,685,215,695);
	fillrectangle(685,685,695,695);
	setbkmode(TRANSPARENT);//设置文字背景透明
	setcolor(BLACK);//设置文字为黑色
	settextstyle(20,0, "黑体");//设置字体样式: 字体宽度为20像素, 字体名称为"黑体"
	for(int mmm=0 ; mmm<15 ; mmm++){//权值置0
		for(int nnn=0 ; nnn<15 ; nnn++){
			winku[mmm][nnn]=0;
		}
	}
	if(isRobot){
		PlayGame1() ;	//开始人机游戏
	}else{
		PlayGame2() ;	//开始双人游戏
	}
}

