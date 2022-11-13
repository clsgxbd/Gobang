/*----------栈类----------*/
class MyStack {
private:
	Coordinate *m_pBuffer;  //栈空间指针 栈顶
	int m_iSize;				//栈容量 
	int m_iTop;				//栈顶，栈中元素个数
public:
	MyStack(int size);	//分配内存初始化栈空间,设定栈容量,栈顶
	~MyStack();				//回收栈空间内存
	bool stackEmpty(); //判定栈是否为空 ,为空返回true ,非空返回false
	bool stackFull();		//判定栈是否已满,为满返回true ,不满返回false
	void clearStack();	//清空栈
	int	stackLength(); //已有元素的个数
	bool push( bool black , Coordinate elem ); //元素入栈, 栈顶上升
	bool pop( );				//元索出栈 , 栈顶下降，完成悔棋
	bool stackTraverse(  int  _x , int _y , bool isBlack); //遍历栈中元素的坐标 , 与传入坐标比较返回相同或者不同
	bool isWin (   int  _x , int _y , bool black);//判断是否获胜
};

MyStack::MyStack(int size){//分配内存初始化栈空间,设定栈容量,栈顶
	m_iSize = size;
	m_pBuffer = new Coordinate[size];//坐标类型的 数组 
	m_iTop=0;
}
MyStack:: ~MyStack() {//回收栈空间内存
	delete []m_pBuffer ;
}

bool MyStack::stackEmpty(){ //判定栈是否为空 ,为空返回true ,非空返回false
	if(0== m_iTop){ //if(m._iTop== 0)
		return true;
	}
	return false; 
}

bool MyStack::stackFull(){//判定栈是否已满,为满返回true ,不满返回false
	if(m_iTop== m_iSize){ //>=
		return true;
	}
	return false;
}

void MyStack::clearStack(){ //清空栈
	m_iTop= 0;
}

int MyStack::stackLength(){ //已有元素的个数
	return m_iTop;
}

bool MyStack::push( bool black ,Coordinate elem){//元素入栈, 栈顶上升
	//如果当前坐标有棋子(已经入栈)或者棋盘没有空位(栈满)
	if( stackTraverse( elem.GetX() , elem.GetY() ,!black) ||  stackTraverse( elem.GetX() , elem.GetY() ,black)  || stackFull() ) {
		return black;	//入栈失败 ， 玩家不变
	}		
	elem.ChessPieces(black);//落子
	m_pBuffer[m_iTop] = elem;
	m_iTop++;//入栈成功
	return !black ;//切换玩家
}

bool MyStack::pop(){//元索出栈,栈顶下降，完成悔棋
	if( stackEmpty() ){
		return false;
	}
	m_iTop--;
	m_pBuffer[m_iTop].Restore() ;
	return true;
}

bool MyStack::stackTraverse( int  _x , int _y , bool isBlack) {//遍历栈中所有元素的坐标 , 与传入坐标比较返回相同或者不同
	if(true == isBlack) {
		for(int i=0 ; i< m_iTop ; i+=2){//偶遍历；
			if(	m_pBuffer[i]. GetX() == _x  &&	m_pBuffer[i]. GetY() == _y ) return true ;
		}
	}else {
		for(int i=1 ; i< m_iTop ; i+=2){//奇遍历；
			if(	m_pBuffer[i]. GetX() == _x  &&	m_pBuffer[i]. GetY() == _y ) return true ;
		}
	}
	return false ;
}

bool MyStack::isWin(int _x , int _y , bool black  ){//判断是否获胜
	int i = _x ;
	int j = _y ;
	int k=0 , num=1;//计数器置1

	//正对角线判断
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右下方相邻有无同色子
		if ( stackTraverse( i+60*k, j+60*k , black ) ) {
			num++ ; 
		}else {
			for ( k=1 ; k<5 ; k++ )	{
				if ( stackTraverse( i-60*k, j-60*k , black ) ) num++ ; //判断当前落子左上方相邻有无同色子
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;

	//反对角线判断
	num=1;//计数器置1
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右上方相邻有无同色子
		if ( stackTraverse( i+60*k, j-60*k , black ) ) {
			num++ ; 
		}else {
			for ( k=1 ; k<5 ; k++ )	{ //判断当前落子左下方相邻有无同色子
				if ( stackTraverse( i-60*k, j+60*k , black ) ) {
					num++ ;
				}
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;

	//横向判断
	num=1;//计数器置1
	for ( k=1 ; k<5 ; k++  ){//判断当前落子右方相邻有无同色子
		if ( stackTraverse( i+60*k, j , black ) ){
			num++ ; 
		} else {
			for ( k=1 ; k<5 ; k++ )	{
				if ( stackTraverse( i-60*k, j , black ) ) num++ ; //判断当前落子左方相邻有无同色子
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;

	//纵向判断
	num=1;//计数器置1
	for ( k=1 ; k<5 ; k++  ){//判断当前落子下方相邻有无同色子
		if ( stackTraverse( i, j+60*k , black ) ){
			num++ ; 
		} else{
			for ( k=1 ; k<5 ; k++ )	{
				if ( stackTraverse( i, j-60*k , black ) ) num++ ; //判断当前落子上方相邻有无同色子
				else break;
			}
			break ;
		}
	}
	if( 5 <= num)  return true ;
	return false ;
}
