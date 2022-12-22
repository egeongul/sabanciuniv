package com.sabanciuniv.repo;

import java.util.List;

import org.springframework.data.mongodb.repository.MongoRepository;


import com.sabanciuniv.model.accounts;


public interface accountRepo extends MongoRepository<accounts, String>{

	public List<accounts> findByid(String Id);
	
}
