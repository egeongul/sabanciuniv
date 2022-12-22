package com.sabanciuniv.model;

public class transactionWithAccs {
	accounts from;
	accounts to;
	double amount;
	String createDate;
	public accounts getFrom() {
		return from;
	}
	public void setFrom(accounts from) {
		this.from = from;
	}
	public accounts getTo() {
		return to;
	}
	public void setTo(accounts to) {
		this.to = to;
	}
	public double getAmount() {
		return amount;
	}
	public void setAmount(double amount) {
		this.amount = amount;
	}
	
	public transactionWithAccs(accounts from, accounts to, double amount, String createDate) {
		super();
		this.from = from;
		this.to = to;
		this.amount = amount;
		this.createDate = createDate;
	}
	public String getCreateDate() {
		return createDate;
	}
	public void setCreateDate(String createDate) {
		this.createDate = createDate;
	}
	public transactionWithAccs() {
		super();
	}
	
	
	
	
	
}
