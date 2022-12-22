package com.sabanciuniv.model;

import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class JSONresponse {
	String message;
	accounts data;
	
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	public accounts getData() {
		return data;
	}
	public void setData(accounts data) {
		this.data = data;
	}
	public JSONresponse(String message, accounts data) {
		super();
		this.message = message;
		this.data = data;
	}
	public JSONresponse() {
		super();
	}
	
	@Override
	public String toString() {
		return "JSONresponse [message=" + message + ", data=" + data + "]";
	}
	
}
