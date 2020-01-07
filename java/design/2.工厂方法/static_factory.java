interface Human {
     /* 获取人种肤色 */
     public void getColor();
     /* 测试接口 */
     public void talk();
}

class BlackHuman implements Human {
	public void getColor(){
		System.out.println("黑色人种的皮肤颜色是黑色的！");
	}
	public void talk() {
		System.out.println("黑人会说话，一般人听不懂。");
	}
}

class YellowHuman implements Human {
	public void getColor(){
		System.out.println("黄色人种的皮肤颜色是黄色的！");
	}
	public void talk() {
		System.out.println("黄色人种会说话，一般说的都是双字节。");
	}
}

class WhiteHuman implements Human {
	public void getColor(){
		System.out.println("白色人种的皮肤颜色是白色的！");
	}
	public void talk() {
		System.out.println("白色人种会说话，一般都是但是单字节。");
	}
}

/* 将工厂类的createHuman设置为静态方法，省去工厂类的实例化 */
class HumanFactory {
	public static <T extends Human> T createHuman(Class<T> c){

		T human = null;
		try {
			/* 产生一个人类 */
			human = c.newInstance();
		} catch (Exception e) {
			System.out.println("人种生成错误！");
		}
		return human;
	}
}

public class static_factory {
	public static void main(String[] args) {            
		/* 造一个白种人 */
		System.out.println("--造出的第一个人是白色人种--");
		Human whiteHuman = HumanFactory.createHuman(WhiteHuman.class);
		whiteHuman.getColor();
		whiteHuman.talk();         
		/* 造一个黑种人 */
		System.out.println("\n--造出的第二个人是黑色人种--");
		Human blackHuman = HumanFactory.createHuman(BlackHuman.class);
		blackHuman.getColor();
		blackHuman.talk();         
		/* 造一个黄种人 */
		System.out.println("\n--造出的第三个人是黄色人种--");
		Human yellowHuman = HumanFactory.createHuman(YellowHuman.class);
		yellowHuman.getColor();
		yellowHuman.talk();
	}
}