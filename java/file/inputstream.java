import java.io.FileInputStream;
import java.io.File;

public class inputstream{
	public static void main(String[] args) throws Exception{
		/* 1.定义文件路径 */
		File file = new File("." + File.separator + "1.txt");
		
		/* 2.判断文件是否存在 */
		if (file.exists()){
			/* 使用stream进行文件读写 */
			FileInputStream input = new FileInputStream(file);
			byte data[] = new byte[1024];
			
			int len = input.read(data);
			input.close();
			
			/* 输出读取出来的文件内容 */
			System.out.println(new String(data, 0, len));
		}
				
	}
}