#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


using namespace std;

//data_structure.h

struct input {
	int height;
	int prev_block;
	string prevTxID;
	int prevTxOutIndex;
	string scriptSig;
	string txid;
};

vector<input> inputs;

struct output {
	int height;
	int index;
	int value;
	string txid;
	string script;
};

vector<output> outputs;

struct transaction {
	int height = -1;
	int input_count;
	int output_count;
	vector<input> inp_in_tx;
	vector<output> outp_in_tx;
	int is_coinbase;
	string txid;
};

vector<transaction> transactions;

struct block {
	int height = -1;
	int nonce;
	vector<transaction> tx_in_block;
	string hash;
	string prevHash;
	string merkleRoot;
};

vector<block> blocks;



struct Linklist {
	int length;
	block block_info;
	struct Linklist* next;
};





// operations.h

void Read_Blocks(vector<block>& blocks, string datafile) 
{

	string line;
	ifstream f;
	f.open(datafile.c_str(), ios::in);
	f.seekg(36, ios::cur);
	//if (f) cout << "succeed" << endl;
	int i, j;
	//auto it = blocks.begin();//might be wrong
	while (getline(f, line)) 
	{
		i = 0, j = 0;
		string info[5];
		while (line[i] != '\0')
		{
			string l = "";
			while (line[i] != ',' && line[i] != '\0') 
			{
				l = l + line[i];
				i++;
			}
			if (line[i] != '\0')
				i++;
			info[j] = l;
			j++;
		}

		// This form is wrong somehow
		/*it->height = stoi(info[0]);
		it->hash = info[1];
		it->prevHash = info[2];
		it->merkleRoot = info[3];
		it->nonce = stoi(info[4]);
		it++;*/

		//This form is right
		block tmp;
		tmp.height = atoi(info[0].c_str());
		tmp.hash = info[1];
		tmp.prevHash = info[2];
		tmp.merkleRoot = info[3];
		tmp.nonce = atoi(info[4].c_str());
		blocks.push_back(tmp);
	}
}

void Read_Transactions(vector<transaction>& transactions, string datafile) 
{
	string line;
	ifstream f;
	f.open(datafile.c_str());
	f.seekg(48, ios::cur);
	int i, j;
	while (getline(f, line)) 
	{
		i = 0, j = 0;
		string info[5];
		while (line[i] != '\0')
		{
			string l = "";
			while (line[i] != ',' && line[i] != '\0') 
			{
				l = l + line[i];
				i++;
			}
			if (line[i] != '\0')
				i++;
			info[j] = l;
			j++;
		}

		/*auto it = transactions.begin();

		it->height = stoi(info[0]);
		it->txid = info[1];
		it->is_coinbase = stoi(info[2]);
		it->input_count = stoi(info[3]);
		it->output_count = stoi(info[4]);

		it++;*/
		//TODO: change it to the right form
		//your code here:
	}
}

void Read_Inputs(vector<input>& inputs, string datafile) 
{
	string line;
	ifstream f;
	f.open(datafile.c_str());
	f.seekg(56, ios::cur);
	int i, j;
	while (getline(f, line)) 
	{
		i = 0, j = 0;
		string info[6];
		while (line[i] != '\0')
		{
			string l = "";
			while (line[i] != ',' && line[i] != '\0') 
			{
				l = l + line[i];
				i++;
			}
			if (line[i] != '\0')
				i++;
			info[j] = l;
			j++;
		}

		/*auto it = inputs.begin();

		it->height = stoi(info[0]);
		it->txid = info[1];
		it->prev_block = stoi(info[2]);
		it->prevTxID = info[3];
		it->prevTxOutIndex = stoi(info[4]);
		it->scriptSig = info[5];

		it++;*/
		//TODO: change it to the right form
		//your code here:
	}
}

void Read_Outputs(vector<output>& outputs, string datafile) 
{
	string line;
	ifstream f;
	f.open(datafile.c_str());
	f.seekg(30, ios::cur);
	int i, j;
	while (getline(f, line)) 
	{
		i = 0, j = 0;
		string info[5];
		while (line[i] != '\0')
		{
			string l = "";
			while (line[i] != ',' && line[i] != '\0') 
			{
				l = l + line[i];
				i++;
			}
			if (line[i] != '\0')
				i++;
			info[j] = l;
			j++;
		}

		auto it = outputs.begin();

		/*it->height = stoi(info[0]);
		it->txid = info[1];
		it->index = stoi(info[1]);
		it->value = stoi(info[3]);
		it->script = info[4];

		it++;*/
		//TODO: change it to the right form
		//your code here:

	}
}


Linklist* Sqblock_to_Linkblock(vector<block> &blocks)
{
	int i = 1;
	Linklist* Header = new Linklist;
	Linklist* p = new Linklist;

	Header->next = p;
	Header->length = 0;


	while (i != blocks.size()) {

		p->length = i;
		p->block_info = blocks[i - 1];                              //something wrong here!
		p = p->next;
		i++;

	}

	return Header;
}

void Print_Length(Linklist* Header) {
	int i = 1;
	Linklist* p;
	p = Header;
	while (p->next != nullptr) {
		p = p->next;
	}
	printf("%d", p->length);
}

void Print_Block(vector<block> &blocks) {
	int i = 0;
	int block_height;
	scanf_s("Please enter block height: %d", &block_height);
	printf("height: %d\n", block_height);
	printf("nonce: %d\n", blocks[block_height].nonce);
	printf("hash: %s\n", blocks[block_height].hash.c_str());
	printf("prevhash: %s\n", blocks[block_height].prevHash.c_str());
	printf("merkleroot: %s\n", blocks[block_height].merkleRoot.c_str());
}

void Print_Transaction(vector<transaction> transactions) {
	int i = 0;
	string txID;
	scanf_s("Please enter txID: %s", &txID);
	while (txID != transactions[i].txid) {
		i++;
	}
	printf("txID: %s", txID.c_str());
	printf("is_coinbase: %d\n", transactions[i].is_coinbase);
	printf("input count: %d\n", transactions[i].input_count);
	printf("output count: %d\n", transactions[i].output_count);
}


int check_transaction_legality(vector<transaction> TransactionToCheck) {
	int i = 0;
	int n = 0;
	int m = 0;
	int p = 0;
	int value[2] = { 0,0 };

	vector<transaction> legal_tx;
	while (TransactionToCheck[i].height != -1) {
		if (TransactionToCheck[i].is_coinbase == 1) {
			legal_tx[p] = TransactionToCheck[i];
			i++;
			p++;
			continue;
		}
		for (n = 0; n < TransactionToCheck.size(); n++) {
			for (m = 0; m < 2; m++) {
				if (TransactionToCheck[i].inp_in_tx[m].prev_block == outputs[n].height && TransactionToCheck[i].height > outputs[n].height) {
					if (TransactionToCheck[i].inp_in_tx[m].prevTxOutIndex == outputs[n].index) {
						value[m] = outputs[n].value;
					}

				}

			}
		}
		if (value[0] + value[1] > TransactionToCheck[i].outp_in_tx[0].value + TransactionToCheck[i].outp_in_tx[1].value) {
			outputs[n].height = -1;
			legal_tx[p] = TransactionToCheck[i];
			i++;
			p++;
		}
	}
	cout << "legal transaction number :" << p << endl;
	cout << "illegal transaction number:" << i - p << endl;
	return 0;
}

// main.cpp

int main() {

	//printf("1\n");

	//¶ÁÈëÊý¾Ý
	// Use absolute path as Argument
	Read_Blocks(blocks, "C:\\Users\\86138\\source\\repos\\RUC_Project\\proZhangJIaRui\\blocks.csv");	//Change it to your absolute path
	//Read_Inputs(inputs, "inputs.csv");
	//Read_Outputs(outputs, "outputs.csv");
	//Read_Transactions(transactions, "transactions.csv");

	////printf("2\n");

	//Print_Length(Sqblock_to_Linkblock(blocks));

	////printf("3\n");

	//check_transaction_legality(transactions);

	////printf("4\n");

	//Print_Block(blocks);

	////printf("5");

	//Print_Transaction(transactions);
	cout << blocks.size();

	return 0;
}
