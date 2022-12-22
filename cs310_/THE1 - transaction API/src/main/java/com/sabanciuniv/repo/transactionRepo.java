package com.sabanciuniv.repo;


import java.util.List;

import org.springframework.data.mongodb.repository.MongoRepository;

import com.sabanciuniv.model.transactions;

public interface transactionRepo extends MongoRepository<transactions, String>{
	
	public List<transactions> findByfromAccountId(String title);
	public List<transactions> findBytoAccountId(String title);
	
}
