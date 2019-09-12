class NewException extends Exception{	//此类型要强制处理
	public NewException(String msg){
		super(msg);						//调用父类构造
	}
}

public class newexception{
	public static void main(String[] args){
		int num = 20;
		
		try{
			if (num > 10){
				throw new NewException("数值过大");	//使用throw主动抛出异常
			}
		} catch (Exception e){
			e.printStackTrace();
		}
	}
} 