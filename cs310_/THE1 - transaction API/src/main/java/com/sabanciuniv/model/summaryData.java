package com.sabanciuniv.model;

import java.util.List;

public class summaryData {
	String id;
	String owner;
	String createDate;
	List<transactionWithAccs> transactionOut;
	List<transactionWithAccs> transactionIn;
	Double balance;
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getOwner() {
		return owner;
	}
	public void setOwner(String owner) {
		this.owner = owner;
	}
	public String getCreateDate() {
		return createDate;
	}
	public void setCreateDate(String createDate) {
		this.createDate = createDate;
	}
	public List<transactionWithAccs> getTransactionOut() {
		return transactionOut;
	}
	public void setTransactionOut(List<transactionWithAccs> transactionOut) {
		this.transactionOut = transactionOut;
	}
	public List<transactionWithAccs> getTransactionIn() {
		return transactionIn;
	}
	public void setTransactionIn(List<transactionWithAccs> transactionIn) {
		this.transactionIn = transactionIn;
	}
	
	public summaryData(String id, String owner, String createDate, List<transactionWithAccs> transactionOut,
			List<transactionWithAccs> transactionIn, Double balance) {
		super();
		this.id = id;
		this.owner = owner;
		this.createDate = createDate;
		this.transactionOut = transactionOut;
		this.transactionIn = transactionIn;
		this.balance = balance;
	}
	
	public Double getBalance() {
		return balance;
	}
	public void setBalance(Double balance) {
		this.balance = balance;
	}
	
	
	
}
