package com.sabanciuniv.model;

import java.util.List;

public class transactionTo {
	String message;
	List<transactionWithAccs>data;
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public List<transactionWithAccs> getData() {
		return data;
	}
	public void setData(List<transactionWithAccs> data) {
		this.data = data;
	}
	public transactionTo(String message, List<transactionWithAccs> data) {
		super();
		this.message = message;
		this.data = data;
	}
	public transactionTo() {
		super();
	}
	
}
