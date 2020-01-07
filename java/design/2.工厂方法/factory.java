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

/* 以泛型形式构造对象，泛型声明继承关系 */
abstract class AbstractHumanFactory {
     public abstract <T extends Human> T createHuman(Class<T> c);
}

class HumanFactory extends AbstractHumanFactory {
	public <T extends Human> T createHuman(Class<T> c){

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

public class factory {
	public static void main(String[] args) {
		/* 声明一个工厂 */
		AbstractHumanFactory YinYangLu = new HumanFactory();               
		/* 造一个白种人 */
		System.out.println("--造出的第一个人是白色人种--");
		Human whiteHuman = YinYangLu.createHuman(WhiteHuman.class);
		whiteHuman.getColor();
		whiteHuman.talk();         
		/* 造一个黑种人 */
		System.out.println("\n--造出的第二个人是黑色人种--");
		Human blackHuman = YinYangLu.createHuman(BlackHuman.class);
		blackHuman.getColor();
		blackHuman.talk();         
		/* 造一个黄种人 */
		System.out.println("\n--造出的第三个人是黄色人种--");
		Human yellowHuman = YinYangLu.createHuman(YellowHuman.class);
		yellowHuman.getColor();
		yellowHuman.talk();
	}
}