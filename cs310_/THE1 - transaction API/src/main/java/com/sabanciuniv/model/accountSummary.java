package com.sabanciuniv.model;

import java.util.List;

public class accountSummary {
	
	String message;
	summaryData data;
	
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public summaryData getData() {
		return data;
	}
	public void setData(summaryData data) {
		this.data = data;
	}
	
	public accountSummary(String message, summaryData data) {
		super();
		this.message = message;
		this.data = data;
	}
	public accountSummary() {
		super();
	}
	
	
	
	
}
