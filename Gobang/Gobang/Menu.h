/*--------��ʼ�˵���--------*/
class Menu {
public:
	//�˵����溯��������������
	int Menuface(){	
		initgraph(1200, 900); //��ʼ��һ��1200*900��ͼ�ν���
		SetWindowText(GetHWnd(), "��������Ϸ");//���ô��ڱ���
		loadimage( 0,  ("static\\image\\�˵�����.jpg")	); //��ʾ����ͼƬ
		PlaySound("static\\sound\\BGM.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//���ű�������
		int i = 0 , j = 0 ;  
		int _X=720 , _Y=420;
		bool isOpen[4]={true,true,true,true};
		IMAGE img[4][4];// ���� IMAGE ����
		//////����ͼƬ//////
		loadimage(&img[0][0],"static\\image\\��ʼ��Ϸ_ѡ��.jpg");
		loadimage(&img[1][0],"static\\image\\��սģʽ�˻�_ѡ��.jpg");
		loadimage(&img[2][0],"static\\image\\�������ֿ�_ѡ��.jpg");
		loadimage(&img[3][0],"static\\image\\������Ч��_ѡ��.jpg");
		loadimage(&img[0][1],"static\\image\\��ʼ��Ϸ_��ѡ.jpg");
		loadimage(&img[1][1],"static\\image\\��սģʽ�˻�_��ѡ.jpg");
		loadimage(&img[2][1],"static\\image\\�������ֿ�_��ѡ.jpg");
		loadimage(&img[3][1],"static\\image\\������Ч��_��ѡ.jpg");
		loadimage(&img[0][2],"static\\image\\��ʼ��Ϸ_ѡ��.jpg");
		loadimage(&img[1][2],"static\\image\\��սģʽ˫��_ѡ��.jpg");
		loadimage(&img[2][2],"static\\image\\�������ֹ�_ѡ��.jpg");
		loadimage(&img[3][2],"static\\image\\������Ч��_ѡ��.jpg");
		loadimage(&img[0][3],"static\\image\\��ʼ��Ϸ_��ѡ.jpg");
		loadimage(&img[1][3],"static\\image\\��սģʽ˫��_��ѡ.jpg");
		loadimage(&img[2][3],"static\\image\\�������ֹ�_��ѡ.jpg");
		loadimage(&img[3][3],"static\\image\\������Ч��_��ѡ.jpg");
		putimage(720 , 540,&img[1][1]);
		while(1){
			switch(	_getch()){
			case 13: {//���»س�
					mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					switch(i){//�жϵ�ǰָ��ڼ���
						mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
					case 0 :	
						_X=720 ; _Y=420 ;
						chessboard( isOpen[1],isOpen[3] );	 //��ʼ��Ϸ�������̲���������Ч״̬����
						PlaySound(NULL,NULL,SND_ASYNC);//ֹͣ��������
						return 0 ; 
					case 1 :		_X=720 ; _Y=540 ; break ;
					case 2 :		_X=720 ; _Y=660 ; break ;	
					case 3 :		_X=720 ; _Y=780 ; break ;
					default:	cout<< "����" <<endl;	break ;
					}
					isOpen[i]=! isOpen[i]	;	//�л�״̬
					if(isOpen[i]){		
						putimage( _X ,_Y , &img[i][0]); //��ͼ
						if( 2 == i )		PlaySound("static\\sound\\BGM.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//���ű�������
					}else	{
						putimage( _X ,_Y , &img[i][2]); //��ͼ
						if( 2 == i )		PlaySound(NULL,NULL,SND_ASYNC) ;	//�ر�����
					}break ;}		
			case 80 :	//���¡�����	
				mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//��������
				i++;//��������1
				if( 3< i )	{ i -- ; break ; }
				if(isOpen[i-1])	putimage( _X ,_Y , &img[i-1][1]); //��ͼ
				else	putimage( _X ,_Y , &img[i-1][3]); //��ͼ
				_Y+=120;//����������		
				if(isOpen[i])	putimage( _X ,_Y , &img[i][0]); //��ͼ
				else	putimage( _X ,_Y , &img[i][2]); //��ͼ
				break ;	
			case 72 :	//���¡�����
				mciSendString("play static\\sound\\ѡ��.wav", NULL, 0, 0);//������Ч
				i--; //��������1
				if( 0 > i) 	{ i ++ ; break ; }
				if(isOpen[i+1])	putimage( _X ,_Y , &img[i+1][1]); //��ͼ
				else	putimage( _X ,_Y , &img[i+1][3]); //��ͼ
				_Y-=120;	//����������			
				if(isOpen[i])	putimage( _X ,_Y , &img[i][0]); //��ͼ
				else	putimage( _X ,_Y , &img[i][2]); //��ͼ
				break ;	
			case 27: //����esc
				mciSendString("play static\\sound\\ȷ��.wav", NULL, 0, 0);//������Ч
				return 0 ;
			default	:	break ;
			}
			Sleep(100);//��ֹCPUռ�ù���
		}
		return 0 ;
	}
};
