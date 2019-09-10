class MyThread implements Runnable{
	private boolean flag = true;		//定义线程停止标志位
	
	public void run(){
		int i = 0;
		while (this.flag){
			System.out.println(Thread.currentThread().getName() + "运行，i = " +(i++));
		}
	}
	
	/* 编写停止方法用于停止线程 */
	void stop(){
		this.flag = false;
	}
}

public class threadtostop{
	public static void main(String[] args){
		MyThread my = new MyThread();
		Thread t = new Thread(my, "线程");
		t.start();
		try{
			t.sleep(10);			//线程休眠及对应的抛异常
		} catch(InterruptedException e){
			e.printStackTrace();
		}
		my.stop();
	}
}