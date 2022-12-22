package q1;

public class SpreadSheet implements Printable{
	
	String subject;
	Integer numberOfCollumns;
	Integer numberOfRows;
	
	// default constructor
	public SpreadSheet() {
		super();
	}
	
	// non-default constructor
	public SpreadSheet(String subject, Integer numberOfCollumns, Integer numberOfRows) {
		super();
		this.subject = subject;
		this.numberOfCollumns = numberOfCollumns;
		this.numberOfRows = numberOfRows;
	}
	
	@Override
	public String toString() {
		return "SpreadSheet [subject=" + subject + ", numberOfCollumns=" + numberOfCollumns + ", numberOfRows="
				+ numberOfRows + "]";
	}

	@Override
	public String getContent() {
		return this.toString();
	}

	
	
}
