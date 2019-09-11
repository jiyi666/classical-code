import java.io.FileOutputStream;
import java.io.File;

public class outputstream{
	public static void main(String[] args) throws Exception{
		/* 1.定义文件路径 */
		File file = new File("." + File.separator + "1.txt");
		
		/* 2.使用outputstream进行对象实例化 */
		FileOutputStream output = new FileOutputStream(file);
		//FileOutputStream output = new FileOutputStream(file, true);		//文件接续
		
		/* 3.将字符输出转为字节写入到文件当中 */
		String str = "hello world!";
		byte data[] = str.getBytes();
		output.write(data);
		output.close();
	}
}