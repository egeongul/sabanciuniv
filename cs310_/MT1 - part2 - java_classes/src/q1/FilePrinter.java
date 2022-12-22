package q1;

public class FilePrinter extends Printer {
	
	
	String fileName;
	
	// non-default constructor
	public FilePrinter(String fileName) {
		super();
		this.fileName = fileName;
	}



	@Override
	public void printOut(Printable p) {
		System.out.println("Data printed to the " + fileName);
		System.out.println(p.getContent());
		System.out.println("");
		
	}

}
