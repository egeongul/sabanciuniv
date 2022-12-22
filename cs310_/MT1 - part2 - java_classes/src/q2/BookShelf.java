package q2;

import java.util.ArrayList;

public class BookShelf {
	ArrayList<Book> books;
	Integer numOfBooks;
	
	Integer getTotalNumberOfBooks() {
		return books.size();
	}
	
	Book getBook(Integer idx) {
		return books.get(idx);
	}
	
	
	public ArrayList<Book> getBooks() {
		return books;
	}

	public void setBooks(ArrayList<Book> books) {
		this.books = books;
	}

	public Integer getNumOfBooks() {
		return numOfBooks;
	}
	public void setNumOfBooks(Integer numOfBooks) {
		this.numOfBooks = numOfBooks;
	}
	public BookShelf(ArrayList<Book> books) {
		super();
		this.books = books;
		this.numOfBooks = this.getTotalNumberOfBooks();
	}
	
	
	@Override
	public String toString() {
		return "BookShelf [books=" + books + ", numOfBooks=" + numOfBooks + "]\n";
	}

	String getInfo() {
		return this.toString();
	}
	
	
	
	
}
