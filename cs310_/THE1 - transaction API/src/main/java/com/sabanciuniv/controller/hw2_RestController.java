package com.sabanciuniv.controller;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.sabanciuniv.model.JSONresponse;
import com.sabanciuniv.model.JSONresponseTran;
import com.sabanciuniv.model.accountSummary;
import com.sabanciuniv.model.accounts;
import com.sabanciuniv.model.summaryData;
import com.sabanciuniv.model.transactionTo;
import com.sabanciuniv.model.transactionWithAccs;
import com.sabanciuniv.model.transactions;
import com.sabanciuniv.repo.accountRepo;
import com.sabanciuniv.repo.transactionRepo;

import ch.qos.logback.classic.Logger;
import jakarta.annotation.PostConstruct;


@RestController
public class hw2_RestController {
	
	private static final Logger logger = (Logger) LoggerFactory.getLogger(hw2_RestController.class);
	@Autowired private accountRepo accountRepository;
	@Autowired private transactionRepo transactionRepository;
	
	
	@PostConstruct
	public void init() {
		if(accountRepository.count() == 0) {
			
			//adding accounts
			accounts acc1 = new accounts("1111", "Ege", "11.04.2002");
			accounts acc2 = new accounts("2222", "Arda", "11.04.2002");
			accountRepository.save(acc1);
			accountRepository.save(acc2);
		}
		
		if(transactionRepository.count() == 0) {
			//adding transactions
			transactions tr1 = new transactions("1111", "2222", 1500.0);
			transactions tr2 = new transactions("2222", "1111",  2500.0);
			transactionRepository.save(tr1);
			transactionRepository.save(tr2);
		}
		
	}
	
	@PostMapping("/account/save")
	public JSONresponse saveAccount(@RequestBody accounts acc) {
		if(acc.getId() == null) {
			JSONresponse accountToSave = new JSONresponse("ERROR:missing fields", null);
			//dont save
			return accountToSave;
		}
		else if(acc.getOwner() == null) {
			JSONresponse accountToSave = new JSONresponse("ERROR:missing fields", null);
			//dont save
			return accountToSave;
		}
		
		DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
		 
		LocalDateTime currentLocalDateTime = LocalDateTime.now();
		// Format LocalDateTime to String
	    String formattedDateTime = currentLocalDateTime.format(dateTimeFormatter);
	    acc.setCreateDatee(formattedDateTime);
		JSONresponse accountSaved = new JSONresponse("SUCCES", acc);
		accountRepository.save(acc);
		return accountSaved;
		
	}
	
	
	@PostMapping("/transaction/save")
	public JSONresponseTran saveTran(@RequestBody transactions tr) {
		if(tr.getFromAccountId() == null) {
			JSONresponseTran transToSave = new JSONresponseTran("ERROR: missing fields", null);
			//dont save
			return transToSave;
		}
		else if(tr.getToAccountId() == null) {
			JSONresponseTran transToSave = new JSONresponseTran("ERROR:missing fields", null);
			//dont save
			return transToSave;
		}
		else if(tr.getAmount() == null) {
			JSONresponseTran transToSave = new JSONresponseTran("ERROR:missing fields", null);
			//dont save
			return transToSave;
		}
		
		else if(accountRepository.findByid(tr.getToAccountId()).isEmpty()) {
			JSONresponseTran transToSave = new JSONresponseTran("ERROR: account id", null);
			//dont save
			return transToSave;
		}
		else if(accountRepository.findByid(tr.getFromAccountId()).isEmpty()) {
			JSONresponseTran transToSave = new JSONresponseTran("ERROR: account id", null);
			//dont save
			return transToSave;
		}
		
		DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
		 
		LocalDateTime currentLocalDateTime = LocalDateTime.now();
		// Format LocalDateTime to String
	    String formattedDateTime = currentLocalDateTime.format(dateTimeFormatter);
		
		transactionWithAccs twacc = new transactionWithAccs(accountRepository.findByid(tr.getFromAccountId()).get(0), 
															accountRepository.findByid(tr.getToAccountId()).get(0),
															tr.getAmount(),
															formattedDateTime);
		JSONresponseTran transToSave = new JSONresponseTran("SUCCES", twacc);
		transactionRepository.save(tr);
		return transToSave;
	}
	
	
	@GetMapping("account/{accountId}")
	public accountSummary summarize(@PathVariable String accountId) {
		if(accountRepository.findByid(accountId).size() == 0){
			accountSummary summyDummy = new accountSummary("ERROR:account doesnt exist!", null);
			return summyDummy;
		}
		else {
			
			DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
			 
			LocalDateTime currentLocalDateTime = LocalDateTime.now();
			// Format LocalDateTime to String
		    String formattedDateTime = currentLocalDateTime.format(dateTimeFormatter);
			
			List<transactions> listOut = transactionRepository.findByfromAccountId(accountId);
			List<transactions> listIn = transactionRepository.findBytoAccountId(accountId);
			
			
			
			Double balance = 0.0;
			for(transactions tr: listOut){
				balance = balance - tr.getAmount();
			}
			
			for(transactions tr: listIn){
				balance = balance + tr.getAmount();
			}
			
			//from
			List<transactionWithAccs> trWithAccList = new ArrayList<transactionWithAccs>();
			
			List<transactions> listInn = transactionRepository.findByfromAccountId(accountId);
			
			for(transactions tr: listInn) {
				transactionWithAccs twacc = new transactionWithAccs();
				accounts acc1 = accountRepository.findByid(tr.getToAccountId()).get(0);
				twacc.setTo(acc1);
				
				accounts acc2 = accountRepository.findByid(tr.getFromAccountId()).get(0);
				twacc.setFrom(acc2);
				
				twacc.setAmount(tr.getAmount());
				twacc.setCreateDate(acc2.getCreateDatee());
				trWithAccList.add(twacc);
				
			}
			
			//to
			List<transactionWithAccs> trWithAccList1 = new ArrayList<transactionWithAccs>();
			
			List<transactions> listIn1 = transactionRepository.findBytoAccountId(accountId);
			
			for(transactions tr: listIn1) {
				transactionWithAccs twacc = new transactionWithAccs();
				accounts acc1 = accountRepository.findByid(tr.getFromAccountId()).get(0);
				twacc.setFrom(acc1);
				
				accounts acc2 = accountRepository.findByid(tr.getToAccountId()).get(0);
				twacc.setTo(acc2);
				
				twacc.setAmount(tr.getAmount());
				twacc.setCreateDate(acc1.getCreateDatee());
				trWithAccList1.add(twacc);
				
			}
			
			summaryData sumData = new summaryData(accountRepository.findByid(accountId).get(0).getId(), 
												  accountRepository.findByid(accountId).get(0).getOwner(),
												  accountRepository.findByid(accountId).get(0).getCreateDatee(),
												  trWithAccList,
												  trWithAccList1,
												  balance);
			
			
			accountSummary sum = new accountSummary("SUCCES", sumData); 
			return sum;
			
			
		}
	}
	
	@GetMapping("transaction/to/{accountId}")
	public transactionTo transactionTo(@PathVariable String accountId) {
		
		if(accountRepository.findByid(accountId).get(0) == null) {
			transactionTo trTo = new transactionTo("ERROR:account doesn’t exist", null);
			return trTo;
		}
		
		List<transactionWithAccs> trWithAccList = new ArrayList<transactionWithAccs>();
		
		List<transactions> listIn = transactionRepository.findBytoAccountId(accountId);
		
		for(transactions tr: listIn) {
			transactionWithAccs twacc = new transactionWithAccs();
			accounts acc1 = accountRepository.findByid(tr.getFromAccountId()).get(0);
			twacc.setFrom(acc1);
			
			accounts acc2 = accountRepository.findByid(tr.getToAccountId()).get(0);
			twacc.setTo(acc2);
			
			twacc.setAmount(tr.getAmount());
			twacc.setCreateDate(acc1.getCreateDatee());
			trWithAccList.add(twacc);
			
		}
		
		transactionTo trTo = new transactionTo("SUCCES", trWithAccList);
		return trTo;
	}
	
	@GetMapping("transaction/from/{accountId}")
	public transactionTo transactionFrom(@PathVariable String accountId) {
		
		if(accountRepository.findByid(accountId).get(0) == null) {
			transactionTo trTo = new transactionTo("ERROR:account doesn’t exist", null);
			return trTo;
		}
		
		List<transactionWithAccs> trWithAccList = new ArrayList<transactionWithAccs>();
		
		List<transactions> listIn = transactionRepository.findByfromAccountId(accountId);
		
		for(transactions tr: listIn) {
			transactionWithAccs twacc = new transactionWithAccs();
			accounts acc1 = accountRepository.findByid(tr.getToAccountId()).get(0);
			twacc.setTo(acc1);
			
			accounts acc2 = accountRepository.findByid(tr.getFromAccountId()).get(0);
			twacc.setFrom(acc2);
			
			twacc.setAmount(tr.getAmount());
			twacc.setCreateDate(acc2.getCreateDatee());
			trWithAccList.add(twacc);
			
		}
		
		transactionTo trTo = new transactionTo("SUCCES", trWithAccList);
		return trTo;
	}
}
