package q1;

import java.time.LocalDateTime;

public class Report implements Printable {

	
	String title;
	LocalDateTime reportDate;
	String text;
	
	
	// default constructor
	public Report() {
		super();
	}
	
	
	// non-default constructor
	public Report(String title, LocalDateTime reportDate, String text) {
		super();
		this.title = title;
		this.reportDate = reportDate;
		this.text = text;
	}
	
	@Override
	public String toString() {
		return "Report [title=" + title + ", reportDate=" + reportDate + ", text=" + text + "]";
	}


	@Override
	public String getContent() {
		
		return this.toString();
	}

}
