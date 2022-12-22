package com.sabanciuniv.model;

import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class transactions {
	
	//id ekle
	String fromAccountId;
	String toAccountId;
	Double amount;
	
	//setters and getters
	public String getFromAccountId() {
		return fromAccountId;
	}
	public void setFromAccountId(String fromAccountId) {
		this.fromAccountId = fromAccountId;
	}
	public String getToAccountId() {
		return toAccountId;
	}
	public void setToAccountId(String toAccountId) {
		this.toAccountId = toAccountId;
	}
	public Double getAmount() {
		if(amount == null) {
			return 0.0;
		}
		return amount;
	}
	public void setAmount(Double amount) {
		this.amount = amount;
	}
	
	//constructor with params
	public transactions(String fromAccountId, String toAccountId, Double amount) {
		super();
		this.fromAccountId = fromAccountId;
		this.toAccountId = toAccountId;
		this.amount = amount;
	}
	
	//default consturctor
	public transactions() {
		super();
	}
	
	
	
	
	
	
	
}
