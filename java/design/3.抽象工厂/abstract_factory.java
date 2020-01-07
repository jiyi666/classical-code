interface Human {
     /* 获取人种肤色 */
     public void getColor();
     /* 测试接口 */
     public void talk();
	 /* 获取人种性别 */
	 public void getSex();
}

/* 下面三个为描述人种的抽象类 */
abstract class AbstractBlackHuman implements Human {
	public void getColor(){
		System.out.println("黑色人种的皮肤颜色是黑色的！");
	}
	public void talk() {
		System.out.println("黑人会说话，一般人听不懂。");
	}
}

abstract class AbstractYellowHuman implements Human {
	public void getColor(){
		System.out.println("黄色人种的皮肤颜色是黄色的！");
	}
	public void talk() {
		System.out.println("黄色人种会说话，一般说的都是双字节。");
	}
}

abstract class AbstractWhiteHuman implements Human {
	public void getColor(){
		System.out.println("白色人种的皮肤颜色是白色的！");
	}
	public void talk() {
		System.out.println("白色人种会说话，一般都是但是单字节。");
	}
}

/* 每个抽象类有两个实现类，男性和女性，共3 * 2 = 6 个实现类 */
class FemaleYellowHuman extends AbstractYellowHuman {
	public void getSex() {
		System.out.println("黄人女性");
	}
}

class MaleYellowHuman extends AbstractYellowHuman {
	public void getSex() {
		System.out.println("黄人男性");
	}
}

class FemaleBlackHuman extends AbstractBlackHuman {
	public void getSex() {
		System.out.println("黑人女性");
	}
}

class MaleBlackHuman extends AbstractBlackHuman {
	public void getSex() {
		System.out.println("黑人男性");
	}
}
class FemaleWhiteHuman extends AbstractWhiteHuman {
	public void getSex() {
		System.out.println("白人女性");
	}
}

class MaleWhiteHuman extends AbstractWhiteHuman {
	public void getSex() {
		System.out.println("白人男性");
	}
}


/* 工厂类接口定义 */
interface HumanFactory {
	 /* 制造一个黄色人种 */
     public Human createYellowHuman();
     /* 制造一个白色人种 */
     public Human createWhiteHuman();
     /* 制造一个黑色人种 */
     public Human createBlackHuman();
}

/* 两个工厂实现类 */
class FemaleFactory implements HumanFactory {
	/* 生产出黑人女性 */
	public Human createBlackHuman() {
		return new FemaleBlackHuman();
	}
	/* 生产出白人女性 */
	public Human createWhiteHuman() {  
		return new FemaleWhiteHuman();
	}
	/* 生产出黄人女性 */
	public Human createYellowHuman() {
		return new FemaleYellowHuman();
	}
}		 

class MaleFactory implements HumanFactory {
	/* 生产出黑人男性 */
	public Human createBlackHuman() {
		return new MaleBlackHuman();
	}
	/* 生产出白人男性 */
	public Human createWhiteHuman() {  
		return new MaleWhiteHuman();
	}
	/* 生产出黄人男性 */
	public Human createYellowHuman() {
		return new MaleYellowHuman();
	}
}
	 
public class abstract_factory {
	public static void main(String[] args) {            
		/* 男性生产线 */
		HumanFactory maleHumanFactory = new MaleFactory();         
		/* 女性生产线 */
		HumanFactory femaleHumanFactory = new FemaleFactory();             

		Human maleYellowHuman = maleHumanFactory.createYellowHuman();              
		Human femaleYellowHuman = femaleHumanFactory.createYellowHuman();  
		System.out.println("---生产一个黄色女性---");
		femaleYellowHuman.getColor();
		femaleYellowHuman.talk();
		femaleYellowHuman.getSex();                
		System.out.println("\n---生产一个黄色男性---");
		maleYellowHuman.getColor();
		maleYellowHuman.talk();
		maleYellowHuman.getSex();    
	}
}