//
// Created by Mindaugas on 2020-11-06.
//

#include <algorithm>
#include "TransactionGenerator.h"
#include "RNG.h"
#include "hashes/Hash_Generator.h"

vector<Transaction> TransactionGenerator::pickFromUsers(vector<User> users, int number) {
    vector<Transaction> transactions = vector<Transaction>();

    int any = RNG::rangeRandom(0, users.size());

    for(int i = 0; i < number; i++){
            //paima du userius
            User sender = users.at(any);
            any = RNG::rangeRandom(0, users.size());
            User receiver = users.at(any);
        do{
            any = RNG::rangeRandom(0, users.size());
            sender = users.at(any);
            any = RNG::rangeRandom(0, users.size());
            receiver = users.at(any);
        } while(receiver == sender); //isitikina kad nevienodi

        float amount = (float) RNG::rangeRandom(0, sender.getBalance());
        if(sender.getBalance() - amount <= 0){
            continue;
        } else {
            sender.addBalance(-1.0f*amount);
            receiver.addBalance(amount);
        }

        Transaction t = Transaction(sender, receiver, amount);
        transactions.push_back(t);
    }
    return transactions;
}

string TransactionGenerator::getMerkleRoot(const vector<Transaction> &transactionPool) {
    vector<Transaction> transactions = transactionPool;
    sort(transactions.begin(), transactions.end(),
            [](const Transaction& a, const Transaction& b) -> bool //lambda funkcija rikiavimui
            {
                return a.getHash() > b.getHash();
            });
    bc::hash_list transactionList;
    for(const Transaction& t : transactions){
	array<unsigned char, 32> hashStr;
	string tx_hash = t.getHash();
    	for(int i = 0; i < 32; i++){
			hashStr[i] = tx_hash[i];
		}
		transactionList.push_back(hashStr);
    }
    //gauname sakni
	const bc::hash_digest merkle_root = create_merkle(transactionList);
	
    return bc::encode_base16(merkle_root);
}

bc::hash_digest TransactionGenerator::create_merkle(bc::hash_list& merkle){
	if(merkle.empty()) return bc::null_hash;
	else if(merkle.size()==1) return merkle[0];
// While there is more than 1 hash in the list, keep looping...
	while(merkle.size()>1){// If number of hashes is odd, duplicate last hash in the list.
		if(merkle.size()%2!=0) merkle.push_back(merkle.back());
// List size is now even.
		assert(merkle.size()%2==0);// New hash list.        
		bc::hash_list new_merkle;// Loop through hashes 2 at a time.
		for(auto it = merkle.begin(); it != merkle.end(); it +=2){
// Join both current hashes together (concatenate).            
			bc::data_chunk concat_data(bc::hash_size *2);
			auto concat = 	bc::serializer<decltype(concat_data.begin())>(concat_data.begin());            	concat.write_hash(*it);
            concat.write_hash(*(it +1));// Hash both of the hashes.            
bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
// Add this to the new list.            
			new_merkle.push_back(new_root);
		}// This is the new list.        
merkle = new_merkle;
// DEBUG output -------------------------------------        
//std::cout <<"Current merkle hash list:"<< std::endl;
//for(const auto& hash: merkle) std::cout <<"  "<< bc::encode_base16(hash)<< std::endl;
//        std::cout << std::endl;
}// Finally we end up with a single item.
return merkle[0];}


