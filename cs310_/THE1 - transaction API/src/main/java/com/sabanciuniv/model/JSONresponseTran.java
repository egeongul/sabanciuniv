package com.sabanciuniv.model;

import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class JSONresponseTran {
	
	String message;
	transactionWithAccs data;
	
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public transactionWithAccs getData() {
		return data;
	}
	public void setData(transactionWithAccs data) {
		this.data = data;
	}
	
	public JSONresponseTran(String message, transactionWithAccs data) {
		super();
		this.message = message;
		this.data = data;
	}
	
	public JSONresponseTran() {
		super();
	}
	
	
}
