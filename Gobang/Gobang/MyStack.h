/*----------ջ��----------*/
class MyStack {
private:
	Coordinate *m_pBuffer;  //ջ�ռ�ָ�� ջ��
	int m_iSize;				//ջ���� 
	int m_iTop;				//ջ����ջ��Ԫ�ظ���
public:
	MyStack(int size);	//�����ڴ��ʼ��ջ�ռ�,�趨ջ����,ջ��
	~MyStack();				//����ջ�ռ��ڴ�
	bool stackEmpty(); //�ж�ջ�Ƿ�Ϊ�� ,Ϊ�շ���true ,�ǿշ���false
	bool stackFull();		//�ж�ջ�Ƿ�����,Ϊ������true ,��������false
	void clearStack();	//���ջ
	int	stackLength(); //����Ԫ�صĸ���
	bool push( bool black , Coordinate elem ); //Ԫ����ջ, ջ������
	bool pop( );				//Ԫ����ջ , ջ���½�����ɻ���
	bool stackTraverse(  int  _x , int _y , bool isBlack); //����ջ��Ԫ�ص����� , �봫������ȽϷ�����ͬ���߲�ͬ
	bool isWin (   int  _x , int _y , bool black);//�ж��Ƿ��ʤ
};

MyStack::MyStack(int size){//�����ڴ��ʼ��ջ�ռ�,�趨ջ����,ջ��
	m_iSize = size;
	m_pBuffer = new Coordinate[size];//�������͵� ���� 
	m_iTop=0;
}
MyStack:: ~MyStack() {//����ջ�ռ��ڴ�
	delete []m_pBuffer ;
}

bool MyStack::stackEmpty(){ //�ж�ջ�Ƿ�Ϊ�� ,Ϊ�շ���true ,�ǿշ���false
	if(0== m_iTop){ //if(m._iTop== 0)
		return true;
	}
	return false; 
}

bool MyStack::stackFull(){//�ж�ջ�Ƿ�����,Ϊ������true ,��������false
	if(m_iTop== m_iSize){ //>=
		return true;
	}
	return false;
}

void MyStack::clearStack(){ //���ջ
	m_iTop= 0;
}

int MyStack::stackLength(){ //����Ԫ�صĸ���
	return m_iTop;
}

bool MyStack::push( bool black ,Coordinate elem){//Ԫ����ջ, ջ������
	//�����ǰ����������(�Ѿ���ջ)��������û�п�λ(ջ��)
	if( stackTraverse( elem.GetX() , elem.GetY() ,!black) ||  stackTraverse( elem.GetX() , elem.GetY() ,black)  || stackFull() ) {
		return black;	//��ջʧ�� �� ��Ҳ���
	}		
	elem.ChessPieces(black);//����
	m_pBuffer[m_iTop] = elem;
	m_iTop++;//��ջ�ɹ�
	return !black ;//�л����
}

bool MyStack::pop(){//Ԫ����ջ,ջ���½�����ɻ���
	if( stackEmpty() ){
		return false;
	}
	m_iTop--;
	m_pBuffer[m_iTop].Restore() ;
	return true;
}

bool MyStack::stackTraverse( int  _x , int _y , bool isBlack) {//����ջ������Ԫ�ص����� , �봫������ȽϷ�����ͬ���߲�ͬ
	if(true == isBlack) {
		for(int i=0 ; i< m_iTop ; i+=2){//ż������
			if(	m_pBuffer[i]. GetX() == _x  &&	m_pBuffer[i]. GetY() == _y ) return true ;
		}
	}else {
		for(int i=1 ; i< m_iTop ; i+=2){//�������
			if(	m_pBuffer[i]. GetX() == _x  &&	m_pBuffer[i]. GetY() == _y ) return true ;
		}
	}
	return false ;
}

bool MyStack::isWin(int _x , int _y , bool black  ){//�ж��Ƿ��ʤ
	int i = _x ;
	int j = _y ;
	int k=0 , num=1;//��������1

	//���Խ����ж�
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�������·���������ͬɫ��
		if ( stackTraverse( i+60*k, j+60*k , black ) ) {
			num++ ; 
		}else {
			for ( k=1 ; k<5 ; k++ )	{
				if ( stackTraverse( i-60*k, j-60*k , black ) ) num++ ; //�жϵ�ǰ�������Ϸ���������ͬɫ��
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;

	//���Խ����ж�
	num=1;//��������1
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�������Ϸ���������ͬɫ��
		if ( stackTraverse( i+60*k, j-60*k , black ) ) {
			num++ ; 
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //�жϵ�ǰ�������·���������ͬɫ��
				if ( stackTraverse( i-60*k, j+60*k , black ) ) {
					num++ ;
				}
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;

	//�����ж�
	num=1;//��������1
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�����ҷ���������ͬɫ��
		if ( stackTraverse( i+60*k, j , black ) ){
			num++ ; 
		} else {
			for ( k=1 ; k<5 ; k++ )	{
				if ( stackTraverse( i-60*k, j , black ) ) num++ ; //�жϵ�ǰ��������������ͬɫ��
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;

	//�����ж�
	num=1;//��������1
	for ( k=1 ; k<5 ; k++  ){//�жϵ�ǰ�����·���������ͬɫ��
		if ( stackTraverse( i, j+60*k , black ) ){
			num++ ; 
		} else{
			for ( k=1 ; k<5 ; k++ )	{
				if ( stackTraverse( i, j-60*k , black ) ) num++ ; //�жϵ�ǰ�����Ϸ���������ͬɫ��
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;
	return false ;
}
