package q1;

import java.util.ArrayList;

public abstract class Printer{
	ArrayList<Printable> list = new ArrayList<Printable>();
	
	void printAllDocuments() {
		for(Printable s: list) {
			printOut(s);
		}
	}
	
	void addDocument(Printable p) {
		list.add(p);
	}

	public abstract void printOut(Printable p);
	
	
}