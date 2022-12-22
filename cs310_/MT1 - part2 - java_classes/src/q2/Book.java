package q2;

import java.util.ArrayList;

public class Book {
	String title;
	String foreWord;
	ArrayList<Chapter> chapters;
	Integer numOfPages;
	
	Integer getNumberOfPages() {
		Integer sum = 0;
		for(Chapter ch: chapters) {
			sum += ch.pages.size();
		}
		return sum;
	}
	
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getForeWord() {
		return foreWord;
	}
	public void setForeWord(String foreWord) {
		this.foreWord = foreWord;
	}
	public ArrayList<Chapter> getChapters() {
		return chapters;
	}
	public void setChapters(ArrayList<Chapter> chapters) {
		this.chapters = chapters;
	}
	public Book(String title, String foreWord, ArrayList<Chapter> chapters) {
		super();
		this.title = title;
		this.foreWord = foreWord;
		this.chapters = chapters;
		// finding the total number of pages
		Integer sum = this.getNumberOfPages();
		this.numOfPages = sum;
	}
	
	
	@Override
	public String toString() {
		return "Book [title=" + title + ", foreWord=" + foreWord + ", chapters=" + chapters + ", numOfPages="
				+ numOfPages + "]\n";
	}

	String getInfo() {
		return this.toString();
	}
	
	
	
}
