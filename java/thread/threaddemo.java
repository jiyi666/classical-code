public class threaddemo{
	public static void main(String[] args){
		MyThread mt1 = new MyThread();
		MyThread mt2 = new MyThread();
		MyThread mt3 = new MyThread();
		
		Thread t1 = new Thread(mt1, "线程A");
		Thread t2 = new Thread(mt2, "线程B");
		Thread t3 = new Thread(mt3, "线程C");
		
		/* 设置线程优先级 */
		t1.setPriority(Thread.MAX_PRIORITY);
		
		/* 获取线程的优先级 */
		System.out.println("线程A：" + t1.getPriority());
		System.out.println("线程B：" + t2.getPriority());
		System.out.println("线程C：" + t3.getPriority());
		/* 利用Thread启动多线程 */
		t1.start();
		t2.start();
		t3.start();
	}
}


class MyThread implements Runnable{
	
	@Override
	public void run(){
		for(int x = 0; x < 200; x++){
			try{
				Thread.sleep(10);			//线程休眠及对应的抛异常
			} catch(InterruptedException e){
				e.printStackTrace();
			}
			System.out.println(Thread.currentThread().getName() + ", x = " + x);	//获取当前线程的名字
		}
	}
}