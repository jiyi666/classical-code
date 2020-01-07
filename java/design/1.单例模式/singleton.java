public class singleton{
	
	public static void main(String[] args){
	/* 调用三次，看是否只有一个对象生成 */
	for(int i = 0; i < 3; i++){
		Emperor emperor = Emperor.getInstance();
		emperor.say();  
		}		
	}
}

class Emperor{
	
	/* 内部构造唯一的对象 */
	private static final Emperor emperor = new Emperor();
	
	/* 构造函数private化 */
	private Emperor(){
		System.out.println("Constructor Emperor!");
	}
	/* 返回唯一对象 */
	public static Emperor getInstance(){
		return emperor;
	}
	/* 测试对象 */
	public static void say(){
		System.out.println("The only one Emperor is me!");
	}
}