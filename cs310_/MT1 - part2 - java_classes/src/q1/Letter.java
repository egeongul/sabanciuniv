package q1;

public class Letter implements Printable{

	String sender;
	String receiver;
	String textContent;
	
	
	// default constructor
	public Letter() {
		super();
	}
	
	// non-default constructor
	public Letter(String sender, String receiver, String textContent) {
		super();
		this.sender = sender;
		this.receiver = receiver;
		this.textContent = textContent;
	}


	@Override
	public String getContent() {
		return this.toString();
	}

	@Override
	public String toString() {
		return "Letter [sender=" + sender + ", receiver=" + receiver + ", textContent=" + textContent + "]";
	}

}
