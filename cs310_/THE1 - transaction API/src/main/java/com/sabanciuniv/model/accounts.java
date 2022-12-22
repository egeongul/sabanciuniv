package com.sabanciuniv.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class accounts {
	@Id
	String id;
	String owner;
	String createDatee;
	
	//setters and getters
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
	public String getCreateDatee() {
		return createDatee;
	}
	public void setCreateDatee(String createDatee) {
		this.createDatee = createDatee;
	}
	
	//constructor with params
	public accounts(String id, String owner, String createDatee) {
		super();
		this.id = id;
		this.owner = owner;
		this.createDatee = createDatee;
	}
	
	//default constructor
	public accounts() {
		super();
	}
	
	//constructor without primary key
	public accounts(String owner, String createDatee) {
		super();
		this.owner = owner;
		this.createDatee = createDatee;
	}
	
	
	
	//converts data to string
	@Override
	public String toString() {
		return "accounts [id=" + id + ", owner=" + owner + ", createDatee=" + createDatee + "]";
	}
	
	
	
	
	
	
}
