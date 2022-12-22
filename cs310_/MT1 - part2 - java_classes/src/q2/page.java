package q2;

public class page {
	Integer no;
	String content;
	
	public Integer getNo() {
		return no;
	}
	public void setNo(Integer no) {
		this.no = no;
	}
	public String getContent() {
		return content;
	}
	public void setContent(String content) {
		this.content = content;
	}
	
	
	@Override
	public String toString() {
		return "page [no=" + no + ", content=" + content + "]\n";
	}
	
	String getInfo() {
		return this.toString();
	}
	
	public page(Integer no, String content) {
		super();
		this.no = no;
		this.content = content;
	}
	
	
	
}
