/*----------坐标类----------*/
class Coordinate{
private:
	int m_iX;				//横坐标
	int m_iY;				//纵坐标
	IMAGE m_Undo;	//区域截图
public:
	//写入方法
	Coordinate(IMAGE U = NULL ,int x=0, int y=0 )	{
		m_Undo = U ;
		m_iX = x;
		m_iY = y;
	}

	//擦除方法
	void Restore(){		//擦掉上一步的棋子
		putimage(m_iX-30, m_iY-30, &m_Undo); 
	}

	//读取横坐标方法
	int GetX(){
		return m_iX ;
	}

	//读取纵坐标方法
	int GetY(){
		return m_iY ; 
	} 

	// 落子的具体实现
	void ChessPieces( bool black ){
		IMAGE img,chesspieces;// 定义 IMAGE 对象
		getimage(&img, m_iX-30, m_iY-30, m_iX+30, m_iY+30);	// 将当前界面保存区域至 img 对象
		//需要判断是黑子还是白子
		if( black )
		{
			if(Sound ) 	mciSendString("play static\\sound\\黑棋子.wav", NULL, 0, 0);//播放音效
			loadimage(&chesspieces,"static\\image\\黑子.gif");	
		}
		else
		{

			if(Sound ) 	mciSendString("play static\\sound\\白棋子.wav", NULL, 0, 0);//播放音效
			loadimage(&chesspieces,"static\\image\\白子.gif");	
		} 
		HDC dstDC = GetImageHDC();
		HDC srcDC = GetImageHDC(&chesspieces);
		// 使用 Windows GDI 函数实现透明位图
		TransparentBlt(dstDC,m_iX-27, m_iY-27,55, 55, srcDC, 0, 0, 55,55, BLACK);
		// 使 GDI 操作生效
		FlushBatchDraw();
	}
};
