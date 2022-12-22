package q1;

import java.time.LocalDateTime;

public class main {

	public static void main(String[] args) {
		LocalDateTime today = LocalDateTime.now();
		Report rep = new Report("Final Exam",today,"I am trying to complete the question, yeah still!");
		SpreadSheet spSheet = new SpreadSheet("budget", 10, 10);
		Letter lett = new Letter("Jack", "Henry", "Letter content");
		
		FilePrinter fileprinter = new FilePrinter("dosya");
		fileprinter.addDocument(spSheet);
		fileprinter.addDocument(rep);
		fileprinter.addDocument(lett);
		
		ConsolePrinter cslPrint = new ConsolePrinter();
		cslPrint.addDocument(spSheet);
		cslPrint.addDocument(rep);
		cslPrint.addDocument(lett);
		
		
		System.out.println("Printing with console printer: ");
		System.out.println("");
		cslPrint.printAllDocuments();
		
		System.out.println("");
		System.out.println("-------------------------");
		System.out.println("");
		
		
		System.out.println("Printing with file printer: ");
		System.out.println("");
		fileprinter.printAllDocuments();
		
	}

}
