package q2;

import java.util.ArrayList;

public class main {

	public static void main(String[] args) {
		
		page p1 = new page(1, "content1");
		page p2 = new page(2, "content2");
		page p3 = new page(3, "content3");
		page p4 = new page(4, "content4");
		
		ArrayList<page> pages1 = new ArrayList<page>();
		ArrayList<page> pages2 = new ArrayList<page>();
		
		
		pages1.add(p1);
		pages1.add(p2);
		
		pages2.add(p3);
		pages2.add(p4);
		
		Chapter chp1 = new Chapter(1, "Chapter 1", pages1);
		Chapter chp2 = new Chapter(2, "Chapter 2", pages2);
		
		ArrayList<Chapter> chapters1 = new ArrayList<Chapter>(); 
		ArrayList<Chapter> chapters2 = new ArrayList<Chapter>();
		
		chapters1.add(chp1);
		chapters2.add(chp2);
		
		Book book1 = new Book("Book1_title", "Book1_foreWORD", chapters1);
		Book book2 = new Book("Book2_tite", "Book2_foreWORD", chapters2);
		
		ArrayList<Book> myBooks = new ArrayList<Book>(); // max number of books is 100
		
		myBooks.add(book1);
		myBooks.add(book2);
		
		BookShelf shelf = new BookShelf(myBooks);
		
		System.out.println(shelf.getInfo());
		
		System.out.println("-----------");
		System.out.println();
		
		Book pickUpBook = shelf.getBook(1);

		System.out.println("Pick up book:" + pickUpBook.getInfo());
	}

}
