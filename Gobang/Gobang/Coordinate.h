/*----------������----------*/
class Coordinate{
private:
	int m_iX;				//������
	int m_iY;				//������
	IMAGE m_Undo;	//�����ͼ
public:
	//д�뷽��
	Coordinate(IMAGE U = NULL ,int x=0, int y=0 )	{
		m_Undo = U ;
		m_iX = x;
		m_iY = y;
	}

	//��������
	void Restore(){		//������һ��������
		putimage(m_iX-30, m_iY-30, &m_Undo); 
	}

	//��ȡ�����귽��
	int GetX(){
		return m_iX ;
	}

	//��ȡ�����귽��
	int GetY(){
		return m_iY ; 
	} 

	// ���ӵľ���ʵ��
	void ChessPieces( bool black ){
		IMAGE img,chesspieces;// ���� IMAGE ����
		getimage(&img, m_iX-30, m_iY-30, m_iX+30, m_iY+30);	// ����ǰ���汣�������� img ����
		//��Ҫ�ж��Ǻ��ӻ��ǰ���
		if( black )
		{
			if(Sound ) 	mciSendString("play static\\sound\\������.wav", NULL, 0, 0);//������Ч
			loadimage(&chesspieces,"static\\image\\����.gif");	
		}
		else
		{

			if(Sound ) 	mciSendString("play static\\sound\\������.wav", NULL, 0, 0);//������Ч
			loadimage(&chesspieces,"static\\image\\����.gif");	
		} 
		HDC dstDC = GetImageHDC();
		HDC srcDC = GetImageHDC(&chesspieces);
		// ʹ�� Windows GDI ����ʵ��͸��λͼ
		TransparentBlt(dstDC,m_iX-27, m_iY-27,55, 55, srcDC, 0, 0, 55,55, BLACK);
		// ʹ GDI ������Ч
		FlushBatchDraw();
	}
};
