/*--------开始菜单类--------*/
class Menu {
public:
	//菜单界面函数（包括动画）
	int Menuface(){	
		initgraph(1200, 900); //初始化一个1200*900的图形界面
		SetWindowText(GetHWnd(), "五子棋游戏");//设置窗口标题
		loadimage( 0,  ("static\\image\\菜单封面.jpg")	); //显示封面图片
		PlaySound("static\\sound\\BGM.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//播放背景音乐
		int i = 0 , j = 0 ;  
		int _X=720 , _Y=420;
		bool isOpen[4]={true,true,true,true};
		IMAGE img[4][4];// 定义 IMAGE 对象
		//////加载图片//////
		loadimage(&img[0][0],"static\\image\\开始游戏_选中.jpg");
		loadimage(&img[1][0],"static\\image\\对战模式人机_选中.jpg");
		loadimage(&img[2][0],"static\\image\\背景音乐开_选中.jpg");
		loadimage(&img[3][0],"static\\image\\落子音效开_选中.jpg");
		loadimage(&img[0][1],"static\\image\\开始游戏_非选.jpg");
		loadimage(&img[1][1],"static\\image\\对战模式人机_非选.jpg");
		loadimage(&img[2][1],"static\\image\\背景音乐开_非选.jpg");
		loadimage(&img[3][1],"static\\image\\落子音效开_非选.jpg");
		loadimage(&img[0][2],"static\\image\\开始游戏_选中.jpg");
		loadimage(&img[1][2],"static\\image\\对战模式双人_选中.jpg");
		loadimage(&img[2][2],"static\\image\\背景音乐关_选中.jpg");
		loadimage(&img[3][2],"static\\image\\落子音效关_选中.jpg");
		loadimage(&img[0][3],"static\\image\\开始游戏_非选.jpg");
		loadimage(&img[1][3],"static\\image\\对战模式双人_非选.jpg");
		loadimage(&img[2][3],"static\\image\\背景音乐关_非选.jpg");
		loadimage(&img[3][3],"static\\image\\落子音效关_非选.jpg");
		putimage(720 , 540,&img[1][1]);
		while(1){
			switch(	_getch()){
			case 13: {//按下回车
					mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					switch(i){//判断当前指向第几行
						mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
					case 0 :	
						_X=720 ; _Y=420 ;
						chessboard( isOpen[1],isOpen[3] );	 //开始游戏：打开棋盘并将落子音效状态传入
						PlaySound(NULL,NULL,SND_ASYNC);//停止播放音乐
						return 0 ; 
					case 1 :		_X=720 ; _Y=540 ; break ;
					case 2 :		_X=720 ; _Y=660 ; break ;	
					case 3 :		_X=720 ; _Y=780 ; break ;
					default:	cout<< "出错！" <<endl;	break ;
					}
					isOpen[i]=! isOpen[i]	;	//切换状态
					if(isOpen[i]){		
						putimage( _X ,_Y , &img[i][0]); //贴图
						if( 2 == i )		PlaySound("static\\sound\\BGM.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);//播放背景音乐
					}else	{
						putimage( _X ,_Y , &img[i][2]); //贴图
						if( 2 == i )		PlaySound(NULL,NULL,SND_ASYNC) ;	//关闭音乐
					}break ;}		
			case 80 :	//按下“↓”	
				mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音乐
				i++;//行数增加1
				if( 3< i )	{ i -- ; break ; }
				if(isOpen[i-1])	putimage( _X ,_Y , &img[i-1][1]); //贴图
				else	putimage( _X ,_Y , &img[i-1][3]); //贴图
				_Y+=120;//纵坐标下移		
				if(isOpen[i])	putimage( _X ,_Y , &img[i][0]); //贴图
				else	putimage( _X ,_Y , &img[i][2]); //贴图
				break ;	
			case 72 :	//按下“↑”
				mciSendString("play static\\sound\\选择.wav", NULL, 0, 0);//播放音效
				i--; //行数减少1
				if( 0 > i) 	{ i ++ ; break ; }
				if(isOpen[i+1])	putimage( _X ,_Y , &img[i+1][1]); //贴图
				else	putimage( _X ,_Y , &img[i+1][3]); //贴图
				_Y-=120;	//纵坐标上移			
				if(isOpen[i])	putimage( _X ,_Y , &img[i][0]); //贴图
				else	putimage( _X ,_Y , &img[i][2]); //贴图
				break ;	
			case 27: //按下esc
				mciSendString("play static\\sound\\确定.wav", NULL, 0, 0);//播放音效
				return 0 ;
			default	:	break ;
			}
			Sleep(100);//防止CPU占用过高
		}
		return 0 ;
	}
};
