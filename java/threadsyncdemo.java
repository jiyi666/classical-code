/* 同步代码块 */
class MyThread implements Runnable{
	private int ticket = 5;
	
	@Override
	public void run(){
		for (int x =0; x < 20; x++){
			synchronized(this){					//定义同步代码块
				if (this.ticket > 0){			//判断当前是否有剩余票
					try {
						Thread.sleep(100);		//休眠1s，模拟延迟
					}catch (InterruptedException e){
						e.printStackTrace();
					}
					System.out.println(Thread.currentThread().getName() + "买票，ticket = " + this.ticket--);
				}
			}
		}
	}
}

/* 同步方法 */
class MyThread_1 implements Runnable{
	private int ticket = 5;
	
	@Override
	public void run(){
		for (int x =0; x < 20; x++){
			this.sale();
		}
	}
	
	public synchronized void sale(){
		if (this.ticket > 0){			//判断当前是否有剩余票
			try {
				Thread.sleep(100);		//休眠1s，模拟延迟
			}catch (InterruptedException e){
				e.printStackTrace();
			}
			System.out.println(Thread.currentThread().getName() + "买票，ticket = " + this.ticket--);
		}		
	}
}

public class threadsyncdemo{
	public static void main(String[] args) throws Exception{
		//MyThread mt = new MyThread();
		MyThread_1 mt = new MyThread_1();
		new Thread(mt, "票贩子A：").start();
		new Thread(mt, "票贩子B：").start();
		new Thread(mt, "票贩子C：").start();
		new Thread(mt, "票贩子D：").start();
	}
}