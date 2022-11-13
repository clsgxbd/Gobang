/*----------��Ϸ������----------*/

class Game{
public :
	bool agree(bool isR,bool black);	//����ȷ�Ϻ���
	void Add(int i,int j);//���Ȩֵ
	bool PlayGame1();						//������Ϸ���庯��
	bool PlayGame2();						//˫����Ϸ���庯��
	void chessboard(bool isR, bool sound );	//���̺���
};


//����ȷ�Ϻ���
bool agree(bool isR,bool black)	{
	int k,YES1 , YES2 , NO1 , NO2 ;
	IMAGE Back[2];// ���� IMAGE ����
	loadimage(&Back[0],"static\\image\\���1�������.png") ;
	loadimage(&Back[1],"static\\image\\���2�������.png") ;
	if(!isR){
		if( black ){
			putimage( 910 , 400 , &Back[1]); //���2������壬�Ƿ�ͬ�⣿
			YES1 = 'Y' ; YES2 = 'y' ;
			NO1 = 'N' ; NO2 = 'n' ;
		}else{
			putimage( 910 , 400 , &Back[0]); //���1������壬�Ƿ�ͬ�⣿
			YES1 = 55 ; YES2 = 55 ;
			NO1 = 57 ; NO2 = 57 ;
		}
		k=_getch();
		if(YES1==k || YES2==k ){
			if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
			fillrectangle(910 , 400,1155, 520);//��ס������ʾ
			pStack->pop()  ; 	//��ջ
			if(black){	
				//�ֵ����2����
				putimage( 909 , 30 , &Player[1][1]); //С���ѡ��
				putimage( 909 , 600 , &Player[0][0]); //С���ŷ�ѡ
			}else{
				//�ֵ����1����
				putimage( 909 , 600 , &Player[0][1]); //С����ѡ��
				putimage( 909 , 30 , &Player[1][0]); //С��׷�ѡ	
			}
			black= ! black; //�л����
		}
		else if(NO1==k || NO2==k ){
			if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
			fillrectangle(910 , 400,1155, 520);//��ס������ʾ
		}else{
			black=agree( isRobot,black ) ;
		}
		return black ;
	}else{
		if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
		fillrectangle(910 , 400,1155, 520);//��ס������ʾ
		pStack->pop()  ; 	
		pStack->pop()  ; 	
		putimage( 909 , 600 , &Player[0][1]); //С����ѡ��
		putimage( 909 , 30 , &Player[1][0]); //С��׷�ѡ	
		return !black ;
	}
}


//���Ȩֵ
void Add(int x,int y){
	int i=x*60+30;
	int j=y*60+30;
	int k=0 ;
	int num_black=0;//��������0
	int num_white=0;
	//���Խ����ж�
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�������·��������ڰ�ɫ��
		if ( pStack->stackTraverse( i+60*k, j+60*k , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������Ϸ��������ڰ�ɫ��
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
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�������·��������ں�ɫ��
		if ( pStack->stackTraverse( i+60*k, j+60*k , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������Ϸ��������ں�ɫ��
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
	//���Խ����ж�
	num_white=0;//��������0
	num_black=0;
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�������Ϸ��������ڰ�ɫ��
		if ( pStack->stackTraverse( i+60*k, j-60*k , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������·��������ڰ�ɫ��
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
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�������Ϸ��������ں�ɫ��
		if ( pStack->stackTraverse( i+60*k, j-60*k , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������·��������ں�ɫ��
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
	//�����ж�
	num_white=0;//��������0
	num_black=0;
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�����ҷ��������ڰ�ɫ��
		if ( pStack->stackTraverse( i+60*k, j , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������������ڰ�ɫ��
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
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�����ҷ��������ں�ɫ��
		if ( pStack->stackTraverse( i+60*k, j , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������������ں�ɫ��
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
	//�����ж�
	num_white=0;//��������0
	num_black=0;
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�����Ϸ��������ڰ�ɫ��
		if ( pStack->stackTraverse( i, j-60*k , false ) ) {
			num_white++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�����·��������ڰ�ɫ��
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
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�����Ϸ��������ں�ɫ��
		if ( pStack->stackTraverse( i, j-60*k , true) ) {
			num_black++;
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�����·��������ں�ɫ��
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




//������Ϸ���庯��
bool PlayGame1(){
	int i=7 , j=7 , k=1;
	int X , Y ;
	bool black=true ;
	IMAGE img,img2,end;// ��Ź��λ�ûָ�ͼ��������ʾͼҲ����һ�£�
	IMAGE Win[2];// ���ʤ����ʾͼ
	loadimage(&Win[0],"static\\image\\���1ʤ��.png") ;
	loadimage(&Win[1],"static\\image\\���2ʤ��.png") ;
	loadimage(&Player[0][0],"static\\image\\С���ŷ�ѡ.png") ;
	loadimage(&Player[0][1],"static\\image\\С����ѡ��.png") ;
	loadimage(&Player[1][0],"static\\image\\С��׷�ѡ.png") ;
	loadimage(&Player[1][1],"static\\image\\С���ѡ��.png") ;
	putimage( 909 , 600 , &Player[0][1]); //С����ѡ��
	putimage( 909 , 30 , &Player[1][0]); //С��׷�ѡ

	//**���ƹ���ƶ�**//
	do{
		X=(i%15)*60+30 ;  
 		Y=(j%15)*60+30 ;
		getimage(&img, X-30, Y-30, X+30, Y+30);	// ����ǰ���汣�������� img ����
		setlinestyle(PS_SOLID, 2);		//��ʵ�ߣ����Ϊ2����
		setcolor( RED );			//��Ϊ��ɫ
		line(X-28, Y-29, X-28, Y-18 );
		line(X-29, Y-28, X-18, Y-28 );
		line(X-28, Y+28, X-28, Y+18 );
		line(X-28, Y+28, X-18, Y+28 );
		line(X+28, Y+28, X+28, Y+18 );
		line(X+28, Y+28, X+18, Y+28 );
		line(X+28, Y-29, X+18, Y-28 );
		line(X+29, Y-28, X+28, Y-18 );
		setlinecolor( WHITE );			//������Ϊ��ɫ
		setfillcolor( WHITE );				//�����Ϊ��ɫ

		if(27==k){ //��ESC
			if(Sound ) 	mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
			loadimage(&end,"static\\image\\�Ƿ��˳���Ϸ.png") ;
			putimage( 910 , 400, &end); //�Ƿ��˳���Ϸ?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k)
			{	k=_getch();
				switch ( k ){//��¼����
				case 'Y' :
				case 'y' : 	
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					pStack->clearStack();//���ջ
					return false ;
				case 'N':
				case 'n' :	
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					fillrectangle(910 , 400,1155, 520 ) ; 
					break ; //��ס�˳���ʾ
				default :  break ;
				}	
			}
		}

		if(9==k) {//��TAB
			if(Sound ) 	mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
			loadimage(&end,"static\\image\\�Ƿ����¿�ʼ.png") ;
			putimage( 910 , 400, &end); //�Ƿ����¿�ʼ?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k){
				k=_getch();
				switch ( k ){//��¼����
				case 'Y' :
				case 'y' : 	
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					pStack->clearStack();//���ջ
					chessboard( isRobot,Sound );//���¼�������
					return false ;
				case 'N':
				case 'n' :	
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					fillrectangle(910 , 400,1155, 520 ) ; 
					break ; //��ס�˳���ʾ
				default :  break ;
				}
			}
		}
		//������Ҫ�ж��ֵ���һ����˻�
		if(black){ //���1����
			k=_getch();//��¼����
			putimage(X-30, Y-30, &img); ////����ԭ���Ĺ��
			if (32==k ){  //���1�ÿո�����
				black = pStack->push( black , Coordinate ( img , X , Y ) ); //������ջ
				if(false==black){
					winku[(X-30)/60][(Y-30)/60]=-1;
					if( pStack->isWin(  X , Y , !black )  ){	//�����ʤ
						if(Sound )	 mciSendString("play static\\sound\\ʤ��.wav", NULL, 0, 0);//������Ч
						putimage( 910 , 400 , &Win[0]); //��ϲ��� 1��ʤ��
						//��Ȩֵ����
						for(int mmm=0 ; mmm<15 ; mmm++){
							for(int nnn =0 ; nnn<15 ; nnn++){
								winku[mmm][nnn]=0;
							}
						}
						k=_getch();//��¼����
						if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
						pStack->clearStack();//���ջ
						Menu *menu = new Menu();
						menu->Menuface();//���ز˵�����
						return true ;
					}
					//�ֵ����Բ���
					putimage( 909 , 30 , &Player[1][1]); //С���ѡ��
					putimage( 909 , 600 , &Player[0][0]); //С���ŷ�ѡ	
				}
			}
			else if ( 'R'==k || 'r'==k ) { //���1���� R ����
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				if(  ! pStack->stackEmpty()	)
					agree( isRobot,black );//�Ƿ�ͬ�����
			}else if('w'==k || 'W'==k) {
				 j-- ;
				if(0>j) j+=15 ;
				if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}else if('s'==k || 'S'==k) {
				j++ 	;
				if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}else if('a'==k || 'A'==k) {
				 i-- ;
				if(0>i) i+=15 ; 
				if(Sound )	mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}else if('d'==k || 'D'==k){
				i++ ; 
				if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}else ;
		}else{//�˻�����
			putimage(X-30, Y-30, &img); ////����ԭ���Ĺ��
			int maxNum = -1;
			//�����̿հ�λ�����Ȩֵ
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
			getimage(&img2, X-30, Y-30,  X+30, X+30);	// ����ǰ���汣�������� img ����
			Sleep(100);//��ֹCPUռ�ù���
			black=pStack->push( black , Coordinate (  img2, X , Y) );//������ջ
			if(true==black){
				winku[(X-30)/60][(Y-30)/60]=-1;
				if( pStack->isWin(  X ,  Y , !black )  ){	//�����ʤ
					if(Sound )	 mciSendString("play static\\sound\\ʤ��.wav", NULL, 0, 0);//������Ч
					putimage( 910 , 400, &Win[1]); //��ϲ��� 2 ��ʤ��
					for(int mmm=0 ; mmm<15 ; mmm++){//��Ȩֵ����
						for(int nnn=0 ; nnn<15 ; nnn++){
							winku[mmm][nnn]=0;
						}				
					}
					k=_getch();//��¼����
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					pStack->clearStack();//���ջ
					Menu *menu = new Menu();
					menu->Menuface();//���ز˵�����
					return true ;
				}
				//�ֵ�����
				putimage( 909 , 600 , &Player[0][1]); //С����ѡ��
				putimage( 909 , 30 , &Player[1][0]); //С��׷�ѡ		
			}
		}
	}while(1);
}






//˫����Ϸ���庯��
bool PlayGame2(){
	int i=7 , j=7 , k=1;
	int X , Y ;
	bool black=true ;
	IMAGE img,end;// ��Ź��λ�ûָ�ͼ��������ʾͼҲ����һ�£�
	IMAGE Win[2];// ���ʤ����ʾͼ
	loadimage(&Win[0],"static\\image\\���1ʤ��.png") ;
	loadimage(&Win[1],"static\\image\\���2ʤ��.png") ;
	loadimage(&Player[0][0],"static\\image\\С���ŷ�ѡ.png") ;
	loadimage(&Player[0][1],"static\\image\\С����ѡ��.png") ;
	loadimage(&Player[1][0],"static\\image\\С��׷�ѡ.png") ;
	loadimage(&Player[1][1],"static\\image\\С���ѡ��.png") ;
	putimage( 909 , 600 , &Player[0][1]); //С����ѡ��
	putimage( 909 , 30 , &Player[1][0]); //С��׷�ѡ

	//**���ƹ���ƶ�**//
	do
	{
		X=(i%15)*60+30 ;  
		Y=(j%15)*60+30 ;
		getimage(&img, X-30, Y-30, 60, 60);	// ����ǰ���汣�������� img ����
		setlinestyle(PS_SOLID, 2);		//��ʵ�ߣ����Ϊ2����
		setcolor( RED );			//��Ϊ��ɫ
		line(X-28, Y-29, X-28, Y-18 );
		line(X-29, Y-28, X-18, Y-28 );
		line(X-28, Y+28, X-28, Y+18 );
		line(X-28, Y+28, X-18, Y+28 );
		line(X+28, Y+28, X+28, Y+18 );
		line(X+28, Y+28, X+18, Y+28 );
		line(X+28, Y-29, X+18, Y-28 );
		line(X+29, Y-28, X+28, Y-18 );
		setlinecolor( WHITE );			//������Ϊ��ɫ
		setfillcolor( WHITE );			//�����Ϊ��ɫ
		k=_getch();//��¼����
		putimage(X-30, Y-30, &img); ////����ԭ���Ĺ��
		if(27==k) //��ESC
		{
			if(Sound ) 	mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
			loadimage(&end,"static\\image\\�Ƿ��˳���Ϸ.png") ;
			putimage( 910 , 400, &end); //�Ƿ��˳���Ϸ?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k)
			{	k=_getch();
			switch ( k )//��¼����
			{
			case 'Y' :
			case 'y' : 	
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				pStack->clearStack();//���ջ
				return false ;
			case 'N':
			case 'n' :	
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				fillrectangle(910 , 400,1155, 520 ) ; 
				break ; //��ס�˳���ʾ
			default :  break ;
			}	
			}
		}

		if(9==k) //��TAB
		{
			if(Sound ) 	mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
			loadimage(&end,"static\\image\\�Ƿ����¿�ʼ.png") ;
			putimage( 910 , 400, &end); //�Ƿ����¿�ʼ?
			while('Y'!=k&&'y'!=k&&'N'!=k&&'n'!=k)
			{	k=_getch();
			switch ( k )//��¼����
			{
			case 'Y' :
			case 'y' : 	
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				pStack->clearStack();//���ջ
				chessboard( isRobot,Sound );//���¼�������
				return false ;
			case 'N':
			case 'n' :	
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				fillrectangle(910 , 400,1155, 520 ) ; 
				break ; //��ס�˳���ʾ
			default :  break ;
			}	
			}
		}

		//������Ҫ�ж������1/2������
		if(black) //���1����
		{
			if (32==k ){ //���1�ÿո�����
				black = pStack->push( black , Coordinate ( img , X , Y ) ); //������ջ
				if( pStack->isWin(  X , Y , !black )  )	{//�����ʤ
					if(Sound )	 mciSendString("play static\\sound\\ʤ��.wav", NULL, 0, 0);//������Ч
					putimage( 910 , 400 , &Win[0]); //��ϲ��� 1��ʤ��
					k=_getch();//��¼����
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					pStack->clearStack();//���ջ
					Menu *menu = new Menu();
					menu->Menuface();//���ز˵�����
					return true ;
				}
				if(false == black)
				{	//�ֵ����1����
					putimage( 909 , 30 , &Player[1][1]); //С���ѡ��
					putimage( 909 , 600 , &Player[0][0]); //С���ŷ�ѡ		
				}
			}
			else if ( 50 ==k  ) //���2���� ��2�� ����
			{
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				if(  ! pStack->stackEmpty()	)
					black = agree( isRobot,black );//�Ƿ�ͬ�����
			}
			//���1�á�w������s������a������d���������������ƶ����
			else if('w'==k || 'W'==k) 
			{	 j-- ;
			if(0>j) j+=15 ;
			if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}
			else if('s'==k || 'S'==k) 
			{	j++ 	;
			if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}		
			else if('a'==k || 'A'==k) 
			{	 i-- ;
			if(i>0) i+=15 ; 
			if(Sound )	mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}
			else if('d'==k || 'D'==k)
			{	i++ ; 
			if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}
			else ;
		}
		else//���2����
		{	
			if (13==k ){	//���2�ûس�����

				black = pStack->push( black , Coordinate ( img , X , Y ) );//������ջ

				if( pStack->isWin(  X , Y , !black )  ){	//�����ʤ
					if(Sound )	 mciSendString("play static\\sound\\ʤ��.wav", NULL, 0, 0);//������Ч
					putimage( 910 , 400, &Win[1]); //��ϲ��� 2 ��ʤ��
					k=_getch();//��¼����
					if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					pStack->clearStack();//���ջ
					Menu *menu = new Menu();
					menu->Menuface();//���ز˵�����
					return true ;
				}
				if(true == black)
				{	//�ֵ����1����
					putimage( 909 , 600 , &Player[0][1]); //С����ѡ��
					putimage( 909 , 30 , &Player[1][0]); //С��׷�ѡ		
				}

			} 
			else if ( 'R'==k || 'r'==k )  //���1���� R ����
			{	
				if(Sound )	 mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				if(  ! pStack->stackEmpty()	)
					black = agree(isRobot, black );		//�Ƿ�ͬ�����
			}
			//���2�á������������������������������������������ƶ����
			else if(72==k) 
			{	 j-- ;
			if(0>j) j+=15 ;
			if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}
			else if(80==k) 
			{	j++ 	;
			if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}		
			else if(75==k) 
			{	 i-- ;
			if(0>i) i+=15 ; 
			if(Sound )	mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}
			else if(77==k)
			{	i++ ; 
			if(Sound )	 mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
			}
			else ;
		}
	}while(1);
}

//���̺���
void chessboard(bool isR, bool sound ){
	isRobot = isR;//�˻�ģʽ״̬����ȫ�ֱ���isRobot
	Sound = sound ;//��Ч״̬����ȫ�ֱ���Sound
	cleardevice();					//�����Ļ
	loadimage(0,  ("static\\image\\���̱���ͼƬ.jpg")	); 
	setlinestyle(PS_SOLID, 2);		//���Ϊ2����
	setcolor(RGB(0, 0, 0));			//��Ϊ��ɫ
	for(int i = 30; i <= 900; i+=60){//��ʵ��
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
	setbkmode(TRANSPARENT);//�������ֱ���͸��
	setcolor(BLACK);//��������Ϊ��ɫ
	settextstyle(20,0, "����");//����������ʽ: ������Ϊ20����, ��������Ϊ"����"
	for(int mmm=0 ; mmm<15 ; mmm++){//Ȩֵ��0
		for(int nnn=0 ; nnn<15 ; nnn++){
			winku[mmm][nnn]=0;
		}
	}
	if(isRobot){
		PlayGame1() ;	//��ʼ�˻���Ϸ
	}else{
		PlayGame2() ;	//��ʼ˫����Ϸ
	}
}

