#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stddef.h>
#include <vector>
using namespace std;
struct KV{
	string key;
	string value;
	void print(){
        cout<<"键值对<"<<key<<"="<<value<<">"<<endl;
	}
};

struct Node{

	string  tag;
	vector<KV> kvList;
	map<string, Node* > childMap;
	Node* root;
	bool end;//一个完整节点 有<>  </>
	Node(){
		end=false;
		root=NULL;
	}
	~Node(){
	    //cout<<"~delete\n";
        map<string,Node*>::iterator it;
        for(it=childMap.begin();it!=childMap.end();++it){
            delete it->second;
        }
	}
	void print(){
			cout<<"节点<"<<tag<<">"<<endl;
			/*if(kvList.size()==0){
               cout<<"null kvList"<<endl;
			}*/
			for(int i=0;i<kvList.size();i++){
                kvList[i].print();
			}
	}
};
void print(Node* node)
{
        if(node!=NULL){
                node->print();
                map<string,Node*>::iterator it;
                for(it=node->childMap.begin();it!=node->childMap.end();++it){
                        print(it->second);
                }
        }
}


void checkEnd(Node* node,bool &end)
{       
        if(node!=NULL){
		if(end==false||node->end==false){
			end=false;
			return ;
		}
                map<string,Node*>::iterator it;
                for(it=node->childMap.begin();it!=node->childMap.end();++it){
                        checkEnd(it->second,end);
                }
        }else{
		end=false;
		return;	
	}
	end=true;
}


Node *search(Node* node,string key,string value){
	cout<<"search---------------\n";
	if(node==NULL)
	{
		cout<<"search node==NULL ---------------\n";
		return NULL;
	}else{
		map<string,Node*>::iterator it;
        it=node->childMap.begin();
        //it->second->print();
	map<string,Node*>::iterator tt=(it->second->childMap).begin();
	for (;tt!=(it->second->childMap).end();tt++){
		//cout<<tt->first<<":";
		//(tt->second)->print();
		//for(int i=0;i<tt->kvList.size();i++){
		// tt->kvList[i].print();
		//}
		//cout<<"cmd:"<<n->tag<<endl;
		//tt->second->print();
		for (int i=0;i< tt->second->kvList.size();i++){
			if(tt->second->kvList[i].key==key && tt->second->kvList[i].value==value)
			{
				//tt->second->kvList[i].print();
				//tt->second->print();
				return tt->second;
			}
		}
	}

	}
	return NULL;
}


void trim(string *str,string split=" \t\n")
{
	str->erase(0,str->find_first_not_of(split));
	str->erase(str->find_last_not_of(split) + 1);
}
Node* parse()
{
	ifstream in("test.txt");
	string str;
	if (!in.is_open())
	{
		cout << "Error opening file";
		return NULL;
	}
	Node *tree=NULL;
	Node* root;
	root=NULL;
	while (getline(in,str))
	{	
		trim(&str);
		if (str.empty())
			continue;
		if (str.at(0)=='#'){//注释
			cout<<"# continue"<<endl;
			continue;
		}
		//cout<<str<<endl;
		if (str.length()<3){//一行最少3个字符
			cout<<"str.length()<3 error"<<endl;
                        return NULL;
		}
		if (str.at(0)=='<' && str.at(str.size()-1)=='>'){ //<> </>
			if (str.at(1)=='/' && str.length() < 4){//</>
				cout<<"str.length()<4 error"<<endl;
                                return NULL;
			}

			if (str.at(1)!='/'){//<aaa> //新节点
				string s=str.substr(1,str.size()-2);
				trim(&s);
				if(s.empty()){//</>
					cout<<"empty error\n";
					return NULL;
				}
				Node * node = new Node;
				node->tag=s ;
				//node->print();
				if (root!=NULL){
					node->root=root;
					node->root->childMap[node->tag]=node;
				}else{
					tree=node;
				}
				root=node;
				node->end=false;
			}else{//</a>
				string s=str.substr(2,str.size()-3);
				trim(&s);
				if(s.empty()){
					cout<<"empty error\n";
					return NULL;
				}
				if (root->tag!=s){
					cout<<"not find error:"<<s<<endl;
                                        return NULL;
				}
				root->end=true;
				root=root->root;
			}
		}else {
			if(0==count(str.begin(), str.end(), '=')){//== aa
			 	cout<<"1= ! error\n";
                        	return NULL;
			}else{//aa=a =a a=
				int index = str.find("=",0);
				if (index<=0 /*|| index==(str.length()-1)*/){//=a
					cout<<"index<=0 || index==str.length()-1 error\n";
                                        return NULL;
				}

				string lstr,rstr;
				lstr.assign(str,0,index);
				trim(&lstr);
				if(lstr.empty()){//=a
                                        cout<<"lstr rempty error\n";
					return NULL;
				}
				rstr.assign(str,index+1,str.length()-index-1);
				trim(&rstr);
				/*if(rstr.empty()){//a=
					cout<<"rlstr rempty error\n";
					return 1;
				}*/

				KV kv;
				kv.key=lstr;
				kv.value=rstr;
				root->kvList.push_back(kv);
			}
		}
	}
	bool end=true;
	checkEnd(tree,end);
	if(end==false){
		cout<<"no end error----------\n";
		return NULL;
	}
//	cout<<"----------------------\n";
//	print(tree);
	return tree;
}


int main()
{
	//cout<<"test\n";
	Node* tree = parse();
	if (tree==NULL){
		cout<<"***************parse error***************\n";
		return 1;
	}
	string pre_sql_id;
	cout<<"enter pre_sql_id:"<<endl;
	cin>>pre_sql_id;
	
    	Node* node = search(tree,"pre_sql_id",pre_sql_id);
    	if (node!=NULL) node->print();
	if(tree!=NULL)delete  tree;
	return 0;
}
