#include <iomanip>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctype.h>

#include <list>
#include <vector>
#include <map>
using namespace std;



class Node{
public:
  string              symbol;                  

  long long int            dollars;                              
  list<long long int>      dollars_list;                              

  int                 number_donations;
  
  list<Node>          branches;
  map<string,Node*>   branches_map;


  void   input        (list<string>::iterator sym, long int amount);
  void   input        (list<string>::iterator sym, long int amount, long long int number_donations);

  void   output       ( int  depth,  int tabs );
  void   output1      ( int  depth,  int tabs, list<string> head_nodes );


  void   roll_dollars     (int depth);
  void   roll_dollars_sort(int depth);

  int    check_depth(int depth);
  
  Node(){dollars=0;number_donations=0;};
  Node(string name, long long int value ){symbol=name;dollars= value;number_donations=0;/*cout<<name<<" "<<value<<endl;*/}

}; 


//----------------------------------------
//
int
Node::check_depth( int depth){

  if (depth==0) return 1;

  list<Node>::iterator b=branches.begin();

  for (;b!=branches.end();b++){

    int retval = b->check_depth(depth-1);

    if (retval==1) return 1;
  }

  return 0;
}




//----------------------------------------
//
void
Node::roll_dollars( int depth){


  dollars_list.push_front(dollars);

  dollars=0;

  if (depth > 0 ){

    list<Node>::iterator b=branches.begin();

    for (;b!=branches.end();b++){

      //cout<<"r- "<<b->symbol<<endl;

      
      b->roll_dollars(depth-1);
    }
  }

}

//----------------------------------------
//
void
Node::roll_dollars_sort( int depth){


  dollars_list.push_front(dollars);

  dollars=0;

  if (depth > 0 ){

    
    multimap<long long int,Node*>                    br_sort;


    list<Node>::iterator s = branches.begin();

    for (;s!=branches.end();s++){

      long long int d1=0;

      //d1 = atol(s->symbol.c_str());
      d1 = dollars;

      if (d1>-1)
      br_sort.insert(pair<long long int,Node*>(d1, &(*s)));
    }

    
    multimap<long long int,Node*>::iterator  b = br_sort.begin();

    long long int total = 0;
    
    for ( ; b!= br_sort.end(); b++){

      if (b->second->dollars >0) {

	total += b->second->dollars;

	b->second->dollars = total;

      }
    }

    
      list<Node>::iterator b1=branches.begin();

      for (;b1!=branches.end();b1++){

	//cout<<"r- "<<b1->symbol<<endl;

      
	b1->roll_dollars_sort(depth-1);
      }

  }
}



//----------------------------------------
//
void
Node::input( list<string>::iterator symbol, long int amount, long long int number ){

  //cout<< *symbol<<endl;

    dollars += amount;

    number_donations += number;
    
  if (*symbol=="-stop") return;

  
  map< string, Node*>::iterator sn = branches_map.find(*symbol);

   if (sn == branches_map.end()){
    
    Node temp(*symbol, 0 );

    branches.push_back(temp);

    branches_map.insert( pair<string,Node*>(*symbol,&(branches.back() )));
    
    sn = branches_map.find(*symbol);
  }


   //sn->second->dollars += amount;

   sn->second->input( ++symbol, amount, number );
    
}

//----------------------------------------
//
void
Node::input( list<string>::iterator symbol, long int amount){

  //cout<< *symbol<<endl;

    dollars += amount;

    number_donations++;
    
  if (*symbol=="-stop") return;

  
  map< string, Node*>::iterator sn = branches_map.find(*symbol);

   if (sn == branches_map.end()){
    
    Node temp(*symbol, 0 );

    branches.push_back(temp);

    branches_map.insert( pair<string,Node*>(*symbol,&(branches.back() )));
    
    sn = branches_map.find(*symbol);
  }


   //sn->second->dollars += amount;

  sn->second->input( ++symbol, amount );
    
}

//----------------------------------------
//
void
Node::output1( int depth, int tabs, list<string> head_nodes ){


  cout<<symbol;
  //cout<<"\t"<<symbol<<"\t";

  if (depth == 1 ) {
  
    int size = symbol.size();  if (size>60) size=60;

    for (int i=0;i!=60-size;i++) cout<<" ";
    cout<<"\t";

    //cout<<number_donations<<"\t";
  
    for  (int i=0;i!=12;i++) if (dollars<pow(10,i)) cout<<" ";

    cout << dollars ;
    //if (depth==1) cout << dollars ;

    if (number_donations==0) number_donations=-1;
    
    cout<<"\t"<<dollars/number_donations<<"\t"<<number_donations;   //<<"\t"<<branches.size();
  
    list<long long int>::iterator d = dollars_list.begin();

    for ( ; d!=dollars_list.end(); d++){

      //cout<<"\t"<<*d;
      if (depth==1) cout<<"\t"<<*d;
    }

  }  // depth==1
  
  cout << endl;
  
  if (depth-1>0){

      head_nodes.push_back(symbol);
    
    multimap<long long int,Node*>                    br_sort;
    multimap<long long int,Node*>::reverse_iterator  br;

    list<Node>::iterator s = branches.begin();

    int s1=0;
    for (;s!=branches.end();s++,s1++){

      long long int d1=0;
      long long int y1=0;


      if (s->dollars_list.size()>0){

	d1 = s->dollars;

	list<long long int>::iterator dl = s->dollars_list.begin();
	//for (; dl != s->dollars_list.end();dl++) if (*dl>0) y1++;
	for (; dl != s->dollars_list.end();dl++) d1+= *dl;

	//d1=   s->dollars_list.size()*100000  + (s->dollars_list.back())  +y1;

	//cout<<"here"<<endl;
      br_sort.insert(pair<long long int,Node*>(d1, &(*s)));
	
      }else{

 

      d1 = s->dollars;
      //d1 = s->dollars/ s->number_donations;

      //d1 = atol(s->symbol.c_str());

      
      //y1=1;
      //d1 += pow(1000,10);	
      //list<long int>::iterator dl = s->dollars_list.begin();
      //for (; dl != s->dollars_list.end();dl++,y1++) if (d1==0) d1 = -*dl;
      //br_sort.insert(pair<long int,Node*>(s1, &(*s)));
      //br_sort.insert(pair<long int,Node*>(d1+y1, &(*s)));

      if (d1>-1)
      br_sort.insert(pair<long long int,Node*>(d1, &(*s)));
      }

    }
    
    //for (;s!=branches.end();s++) br_sort.insert(pair<long int,Node*>(s->dollars, &(*s)));


    multimap<long long int,Node*>::iterator  b = br_sort.begin();

    long long int total = 0;
    
    for ( ; b!= br_sort.end(); b++){

      if (b->second->dollars >0) b->second->dollars = total + b->second->dollars;

    }

    
    for (br=br_sort.rbegin();br!=br_sort.rend();++br){

      cout<<tabs<<"\t";
      list<string>::iterator h = head_nodes.begin();
      
      for (;h!=head_nodes.end();h++) cout<<*h<<"\t";
      
      //for (int i=0; i!= tabs; i++) cout<<"\t";
      
      br->second->output1(depth-1, tabs+1, head_nodes);
      
    }
    
  }
  
}




//----------------------------------------
//
void
Node::output( int depth, int tabs ){

  cout<<symbol;

  int size = symbol.size();  if (size>60) size=60;

  for (int i=0;i!=60-size;i++) cout<<" ";
  

  for  (int i=0;i!=12;i++) if (dollars<pow(10,i)) cout<<" ";
  cout << dollars ;

  list<long long int>::iterator d = dollars_list.begin();

  for ( ; d!=dollars_list.end(); d++){

    cout<<"\t"<<*d;
  }

  cout << endl;
  
  if (depth-1>0){

    multimap<long int,Node*>                    br_sort;
    multimap<long int,Node*>::reverse_iterator  br;

    list<Node>::iterator s = branches.begin();

    for (;s!=branches.end();s++) br_sort.insert(pair<long int,Node*>(s->dollars, &(*s)));
    
    for (br=br_sort.rbegin();br!=br_sort.rend();++br){

      cout<<symbol;
      
      for (int i=0; i!= tabs+1; i++) cout<<"\t";
  
      br->second->output(depth-1, tabs+1);

    }

  }

}


//----------------------------------------
//
int main1()
{

  string this_year  = "2007";
  string this_month =   "05";
  string this_day   =   "01";

  string year;
  string month;
  string day;

  
  //Node state ("state",0);

  
 

  string         line;
  string         field;

  int            s1=0;
  int            s2=0;

  int count=0;
  int program=0;
  int fund=0;
  string fund_line="";
  int dep_total=0;
  string dept_total_line="";
  int dept=0;
  int dept1=0;
  string dept_line="";
  string dept_line_last="";
  string eal_desc_line ="";

  Node graph1("base node",0);
  
  // ----- parse file


  while (getline(cin, line)){
   
    count++;

    if (line.find("PROGRAM:")==0) program++;
    if (line.find("FUND")==0) {fund++;fund_line=line;}
    
   if (line.find("DEPARTMENT TOTAL")!=std::string::npos) {
     dep_total++;
     dept_total_line=line;

     string n1 = line.substr(line.find("**")+2,26);
     string n2 = ""; if (line.find("**")+26<line.size()) n2=line.substr(line.find("**")+26);

     if (n1.find(",")!=string::npos) n1.erase(n1.find(","),1);
     if (n2.find(",")!=string::npos) n2.erase(n2.find(","),1);

     if (n1.find(".")!=string::npos) n1.erase(n1.find("."),3);
     if (n2.find(".")!=string::npos) n2.erase(n2.find("."),3);

     int s1=1;
     int s2=1;
     
     if (n1.find("-")!=string::npos) {s1=-1; n1.erase(n1.find("-"),1);}
     if (n2.find("-")!=string::npos) {s2=-1; n2.erase(n2.find("-"),1);}
     cout<<n1<<" - "<<n2<<endl;
     int n1i = atoi(n1.c_str());
     int n2i = atoi(n2.c_str());

     cout<<n1i<<" - "<<n2i<<endl;

    list<string>             symbols;

    symbols.clear();

    symbols.push_back("EAL code:"); 
   symbols.push_back(eal_desc_line); 
   symbols.push_back(fund_line); 
  symbols.push_back(dept_line); 
    symbols.push_back("-stop"); 
    graph1.input( symbols.begin(), n1i+n2i );
    
   }


   if (line.find("EAL DESCRIPTION:")==0) eal_desc_line = line.substr(22,100);

   
   if (line.find("DEPT")==0) {
     dept++;
     dept_line=line;
     if (dept_line_last=="") dept_line_last=line;
     if (line!=dept_line_last){

       cout<<eal_desc_line<<endl;
       cout<<dept_line_last<<endl;
       cout<<dept_total_line<<endl;

       dept1++;
       dept_line_last=line;
     }

   }

  }
  cout<<count<<endl;
  cout<<program<<endl;
  cout<<fund<<endl;
  cout<<dep_total<<endl<<endl;  

  cout<<dept<<"  "<<dept1<<endl;
  // ----- parse  file

 




 
   
  list<string> s_e; 

  int ii=0;

  list<Node>::iterator b =graph1.branches.begin();
  for (               ;b!=graph1.branches.end();b++){

    cout<<"--- "<<b->symbol;
    if (b->symbol.size()<12) cout<<"\t";

    cout<<"\t #unique=\t"<<b->branches.size()<<endl; 
    
  }

  

 // -----------------------------------  print out data graph   
    
  b =graph1.branches.begin();
  //b =column_graph.branches.end();
  for (               ;b!=graph1.branches.end();b++){

    
    cout<<endl<<"--- ";    
      b->output1(1,0, s_e);

    if ( b->check_depth(1) ){
      cout<<endl<<"--- ";    
      b->output1(2,0, s_e);
    }
    
   if ( b->check_depth(2) ){
	cout<<endl<<"--- ";    
	b->output1(3,0, s_e);
      }

      if ( b->check_depth(3) ){
	cout<<endl<<"--- ";    
	b->output1(4,0, s_e);
      }

        if ( b->check_depth(4) ){
	cout<<endl<<"--- ";    
	b->output1(5,0, s_e);
      }

       if ( b->check_depth(5) ){
	cout<<endl<<"--- ";    
	b->output1(6,0, s_e);
      }


 





  }



  //ii++;

    return 0;
}

// -----------------------------------  print out data graph    




//----------------------------------------
//
int main2(Node* graph0)
{


  string         line;
  string         field;

  int            s1=0;
  int            s2=0;

  int            first =0;
  int            count=0;

  //Node graph0("fields",0);

  
  

  //----------------------------------------- read the data

    
  while (getline(cin, line)){                //   $ cat datafile.txt | ./a.out > scr.txt

    if (first==1 || line =="-first") {

      first=0;
    
      for (int i = 0;i!=24;i++){     // skip first 24 output lines in fec*.txt files
	getline(cin,line);
      
      }      
    }

    //cout<<line<<endl;

    if (line =="-roll" ){

      cout<<"rolling- "<<graph0->symbol<<endl<<endl;

      
      graph0->roll_dollars(6);
      //graph0-> roll_dollars_sort(6);


      //first=1;

      /*
      list<Node>::iterator b =graph0->branches.begin();
      for (               ;b!=graph0->branches.end();b++){

	cout<<"--- "<<b->symbol;
	if (b->symbol.size()<12) cout<<"\t";

	cout<<"\t #unique=\t"<<b->branches.size()<<endl;     
      }
      */
      
      continue;
    }
    
    count++;

    if ( isdigit( line.c_str()[0] )) {

      //cout<<line<<endl;

      int count1 = atoi(line.substr(0,1).c_str());

      count1 = 2+ (count1);

      int    s1      =0;
      int    s2      =0;
      string field;
      list<string>             symbols;
      list<string>::iterator   s;

      
      s2=line.find("\t", s1); s1+=s2-s1+1;     // skip first field
     
      for (int i=0; i!= count1; i++){

	s2=line.find("\t", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+1;  	

	//remove padding white space

	int last_not_space = 0;
	
	int ii =0;
	
	for ( ;ii< field.length(); ++ii ){

	  if (field[ii] != ' ') last_not_space = ii;
	  
	}

	string field1 = field.substr(0, last_not_space+1);
	
    
	//cout<<"*"<<field1<<"*"<<endl;
	
	//symbols.push_back(field1);
	if (i!=1) symbols.push_back(field1);
      }
      
      symbols.push_back("-stop");

      s2=line.find("\t", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+1;
      int  dollars = atol (field.c_str());
      //cout<<s1<<"-"<<s2<<endl;


      s2=line.find("\t", s1);field=line.substr(s1,s2-s1); s1+=s2-s1+1;
      int  average = atol (field.c_str());
      //cout<<s1<<"-"<<s2<<endl;

      s2=line.find("\n", s1);field=line.substr(s1,line.size()); s1+=s2-s1+1;
      int  number_donations = atol (field.c_str());
      //cout<<s1<<"-"<<s2<<endl;

	
      //cout<<"**"<<field<<endl;

      //cout<<s2<<" "<<dollars<<" "<<average<<"  "<<number_donations<<endl;

	s=symbols.begin();

	//if (*s!="NAME")
	//if (*s=="TRANSACTION_AMT")
	{
	  graph0->input( s, dollars, number_donations);
	  //graph0->input( s, dollars, 1);
	}
      
    } 
 
  }

  //cout<<count<<endl;

  //cout<<graph0->branches_map.size()<<endl;

  list<Node>::iterator b =graph0->branches.begin();
  for (               ;b!=graph0->branches.end();b++){

    cout<<"--- "<<b->symbol;
    if (b->symbol.size()<12) cout<<"\t";

    cout<<"\t #unique=\t"<<b->branches.size()<<endl; 
    
  }




   list<string> s_e;
   
  b =graph0->branches.begin();
  for ( ;b!=graph0->branches.end();b++){

    cout<<endl<<"--- ";      b->output1(2,0, s_e);

   if ( b->check_depth(2) ){
	cout<<endl<<"--- ";    
	b->output1(3,0, s_e);
      }

      if ( b->check_depth(3) ){
	cout<<endl<<"--- ";    
	b->output1(4,0, s_e);
      }

        if ( b->check_depth(4) ){
	cout<<endl<<"--- ";    
	b->output1(5,0, s_e);
      }

       if ( b->check_depth(5) ){
	cout<<endl<<"--- ";    
	b->output1(6,0, s_e);
      }



    
  }




  
 return 0;
}



//----------------------------------------
//
int roll_array( Node* graph0, string field1, string field2)
{

  /*
---     TRANSACTION_TP
0	TRANSACTION_TP	15
1	TRANSACTION_TP	15	TRANSACTION_DT
2	TRANSACTION_TP	15	TRANSACTION_DT	03/2022     	   903233622	513	1758068
  */


  Node graph1(field1, 0);
  
  
  map<string,Node*>::iterator bm = graph0->branches_map.find(field1);

  if (bm != graph0->branches_map.end()){


    list<string> column_titles;
    
    map<string,Node*>::iterator bm1 = bm->second->branches_map.begin();

    for ( ; bm1 != bm->second->branches_map.end(); bm1++){


      //cout<<bm1->second->symbol<<endl;

      column_titles.push_back(bm1->second->symbol);

      
      map<string,Node*>::iterator bm2 = bm1->second->branches_map.find(field2);

      if (bm2 != bm1->second->branches_map.end() ){

	  list<string>             symbols;
	  list<string>::iterator   s;
    
	  map<string,Node*>::iterator bm3 = bm2->second->branches_map.begin();

	  for ( ; bm3 != bm2->second->branches_map.end(); bm3++){

	    //cout<<bm3->second->symbol<<endl;

	    list<string>             symbols;
	    list<string>::iterator   s;
  
	    symbols.push_back(field2);

	    symbols.push_back(bm3->second->symbol);

	    symbols.push_back("-stop");
	    s = symbols.begin();

	    graph1.input(s, bm3->second->dollars);


	    
	  }
	  

      }
      
      graph1.roll_dollars(6);
	  
    }    // bm1

    
    list<string>::reverse_iterator c = column_titles.rbegin();

    cout<<"\t\t";
    
    for ( ;c!=column_titles.rend();++c){

      cout<<*c<<"\t";
      
    }
    cout<<endl;

   list<string> s_e;
   graph1.output1(3,0, s_e);



    
  }


  return 0;
}

//----------------------------------------
//
int make_column1( Node* graph0)
{


  int count[5]={0,0,0,0,0};  
  
  map<string,Node*>::iterator bm = graph0->branches_map.find("NAME");

  if (bm != graph0->branches_map.end()){

    map<string,Node*>::iterator bm1 = bm->second->branches_map.begin();

    for ( ; bm1 != bm->second->branches_map.end(); bm1++){

      list<string>             symbols;

      symbols.push_back("COLUMN1");


      if (bm1->second->dollars <201) { symbols.push_back("200"); count[0]++;}
      if (bm1->second->dollars >200 && bm1->second->dollars <501) { symbols.push_back("500"); count[1]++;}
      if (bm1->second->dollars >500 &&bm1->second->dollars <1001) { symbols.push_back("1000"); count[2]++;}
      if (bm1->second->dollars >1000 &&bm1->second->dollars <5001) { symbols.push_back("5000"); count[3]++;}
      if (bm1->second->dollars >5000 &&bm1->second->dollars >5000) { symbols.push_back("50000"); count[4]++;}

      symbols.push_back("-stop");

      list<string>::iterator   s=symbols.begin();

      graph0->input(s, bm1->second->dollars);

    }
      


  }
  

  return 1;  
}
  
//----------------------------------------
//
int main()
{

  Node graph0;

  graph0.symbol="graph0";

  main1();

  //main2(&graph0);         // read in data from command line into graph0

  //roll_array(&graph0, "TRANSACTION_TP", "TRANSACTION_DT");


  //make_column1(&graph0);

  /*
  list<string> s_e;
   
  list<Node>::iterator b =graph0.branches.begin();
    
  for ( ;b!=graph0.branches.end();b++){

    cout<<endl<<"--- ";      b->output1(2,0, s_e);

  }
  */
     

}
