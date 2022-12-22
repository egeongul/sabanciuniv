package q2;

import java.util.ArrayList;

public class Chapter {
	Integer no;
	String title;
	ArrayList<page> pages;
	
	public Integer getNo() {
		return no;
	}
	public void setNo(Integer no) {
		this.no = no;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public ArrayList<page> getPages() {
		return pages;
	}
	public void setPages(ArrayList<page> pages) {
		this.pages = pages;
	}
	public Chapter(Integer no, String title, ArrayList<page> pages) {
		super();
		this.no = no;
		this.title = title;
		this.pages = pages;
	}
	@Override
	public String toString() {
		return "Chapter [no=" + no + ", title=" + title + ", pages=" + pages + "]\n";
	}
	
	String getInfo() {
		return this.toString();
	}
	
	
	
	
	
}
